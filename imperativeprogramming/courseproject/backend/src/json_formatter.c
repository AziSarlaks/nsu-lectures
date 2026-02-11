#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>
#include "config.h"
#include "json_formatter.h"

static void json_escape_string(const char *input, char *output, int max_len) {
    if (!input || !output || max_len <= 0) {
        if (output && max_len > 0) output[0] = '\0';
        return;
    }
    
    int i = 0, j = 0;
    
    while (input[i] && j < max_len - 1) {
        unsigned char c = (unsigned char)input[i];
        
        // Экранируем специальные символы JSON
        switch (c) {
            case '"': 
                if (j + 2 < max_len) { 
                    output[j++] = '\\'; 
                    output[j++] = '"'; 
                }
                break;
            case '\\': 
                if (j + 2 < max_len) { 
                    output[j++] = '\\'; 
                    output[j++] = '\\'; 
                }
                break;
            case '\b': 
                if (j + 2 < max_len) { 
                    output[j++] = '\\'; 
                    output[j++] = 'b'; 
                }
                break;
            case '\f': 
                if (j + 2 < max_len) { 
                    output[j++] = '\\'; 
                    output[j++] = 'f'; 
                }
                break;
            case '\n': 
                if (j + 2 < max_len) { 
                    output[j++] = '\\'; 
                    output[j++] = 'n'; 
                }
                break;
            case '\r': 
                if (j + 2 < max_len) { 
                    output[j++] = '\\'; 
                    output[j++] = 'r'; 
                }
                break;
            case '\t': 
                if (j + 2 < max_len) { 
                    output[j++] = '\\'; 
                    output[j++] = 't'; 
                }
                break;
            default:
                // Управляющие символы (0x00-0x1F, 0x7F) и непечатаемые символы
                if (c < 32 || c == 127) {
                    // Заменяем на пробел или удаляем
                    output[j++] = ' ';
                } else {
                    // Обычные печатаемые символы
                    output[j++] = c;
                }
                break;
        }
        i++;
    }
    output[j] = '\0';
}

// Функция для полной очистки строки от недопустимых символов
static void json_sanitize_string(const char *input, char *output, int max_len) {
    if (!input || !output || max_len <= 0) {
        if (output && max_len > 0) output[0] = '\0';
        return;
    }
    
    int i = 0, j = 0;
    
    while (input[i] && j < max_len - 1) {
        unsigned char c = (unsigned char)input[i];
        
        // Допустимые символы для JSON строки
        if (c >= 32 && c <= 126 && c != '"' && c != '\\') {
            // Обычные печатаемые символы (кроме кавычек и обратных слешей)
            output[j++] = c;
        }
        else if (c == '"' || c == '\\') {
            // Экранируем кавычки и обратные слеши
            if (j + 2 < max_len) {
                output[j++] = '\\';
                output[j++] = c;
            }
        }
        else if (c == '\n' || c == '\r' || c == '\t') {
            // Экранируем управляющие символы
            if (j + 2 < max_len) {
                output[j++] = '\\';
                if (c == '\n') output[j++] = 'n';
                else if (c == '\r') output[j++] = 'r';
                else if (c == '\t') output[j++] = 't';
            }
        }
        else if (c >= 128 && c <= 255) {
            // UTF-8 символы (частично поддерживаем)
            output[j++] = c;
        }
        // Все остальные символы (0x00-0x1F, 0x7F) игнорируем
        i++;
    }
    output[j] = '\0';
    
    // Если строка пустая после очистки
    if (j == 0 && max_len > 10) {
        strcpy(output, "[unknown]");
    }
}

// Функция для безопасного добавления строки в буфер
static int safe_snprintf(char *buffer, int buffer_size, int offset, const char *format, ...) {
    if (offset >= buffer_size - 1) {
        return 0;
    }
    
    va_list args;
    va_start(args, format);
    int written = vsnprintf(buffer + offset, buffer_size - offset, format, args);
    va_end(args);
    
    if (written < 0 || written >= buffer_size - offset) {
        return 0;
    }
    
    return written;
}

void format_system_info_json(char *buffer, int buffer_size, 
                            CPUStats *cpu, CPUStats *cores, int cores_count,
                            MemoryInfo *mem,
                            GPUInfo *gpu,
                            ProcessInfo *processes, int process_count) {
    // Инициализируем буфер
    if (buffer_size < 1024) {
        snprintf(buffer, buffer_size, "{\"error\":\"buffer too small\"}");
        return;
    }
    
    // Очищаем буфер
    buffer[0] = '\0';
    
    int offset = 0;
    time_t now = time(NULL);
    
    // Начинаем формировать JSON
    offset += safe_snprintf(buffer, buffer_size, offset,
        "{\n"
        "  \"timestamp\": %ld,\n"
        "  \"cpu\": {\n"
        "    \"usage\": %.1f,\n"
        "    \"cores_count\": %d,\n"
        "    \"cores\": [",
        now,
        cpu->usage_percent,
        cores_count);
    
    if (offset == 0) {
        snprintf(buffer, buffer_size, "{\"error\":\"buffer overflow at start\"}");
        return;
    }
    
    // Добавляем информацию о ядрах
    int actual_cores = (cores_count < MAX_CORES) ? cores_count : MAX_CORES;
    for (int i = 0; i < actual_cores; i++) {
        double core_usage = cores[i].usage_percent;
        if (core_usage > 100) core_usage = 100;
        if (core_usage < 0) core_usage = 0;
        
        // Проверяем, нужно ли добавлять запятую
        if (i > 0) {
            if (offset < buffer_size - 2) {
                buffer[offset++] = ',';
                buffer[offset] = '\0';
            }
        }
        
        int written = safe_snprintf(buffer, buffer_size, offset,
            "\n      {\"core\": %d, \"usage\": %.1f}",
            i, core_usage);
        
        if (written > 0) {
            offset += written;
        }
        
        if (offset >= buffer_size - 200) {
            break;
        }
    }
    
    // Закрываем массив cores и переходим к memory
    int written = safe_snprintf(buffer, buffer_size, offset,
        "\n    ]\n"
        "  },\n"
        "  \"memory\": {\n"
        "    \"total\": %llu,\n"
        "    \"used\": %llu,\n"
        "    \"free\": %llu,\n"
        "    \"cached\": %llu,\n"
        "    \"percentage\": %.1f\n"
        "  },\n"
        "  \"gpu\": {\n"
        "    \"usage\": %.1f,\n"
        "    \"memory\": {\n"
        "      \"total\": %llu,\n"
        "      \"used\": %llu\n"
        "    },\n"
        "    \"temperature\": %.1f,\n"
        "    \"power\": %.1f,\n"
        "    \"clock\": %lu,\n"
        "    \"name\": \"%s\"\n"
        "  },\n"
        "  \"processes\": [",
        mem->total, mem->used, mem->free, mem->cached, mem->percentage,
        gpu->usage, gpu->memory_total, gpu->memory_used,
        gpu->temperature, gpu->power, gpu->clock, gpu->name);
    
    if (written > 0) {
        offset += written;
    } else {
        // Если не хватило места, закрываем JSON
        if (offset < buffer_size - 10) {
            strcpy(buffer + offset, "]\n}");
        }
        return;
    }
    
    // Добавляем процессы (максимум 10 для безопасности)
    int limit = (process_count > 10) ? 10 : process_count;
    int processes_added = 0;
    
    for (int i = 0; i < limit; i++) {
        ProcessInfo *p = &processes[i];
        
        // Проверяем, есть ли место (резервируем 500 символов на процесс)
        if (buffer_size - offset < 500) {
            break;
        }
        
        // Очищаем строки
        char safe_cmd[512];
        char safe_name[256];
        
        json_sanitize_string(p->command_line, safe_cmd, sizeof(safe_cmd));
        json_sanitize_string(p->name, safe_name, sizeof(safe_name));
        
        // Убеждаемся, что строки не пустые
        if (strlen(safe_name) == 0) {
            strcpy(safe_name, "unknown");
        }
        if (strlen(safe_cmd) == 0) {
            strcpy(safe_cmd, safe_name);
        }
        
        // Добавляем запятую перед каждым процессом, кроме первого
        if (processes_added > 0) {
            if (offset < buffer_size - 2) {
                buffer[offset++] = ',';
                buffer[offset] = '\0';
            }
        }
        
        written = safe_snprintf(buffer, buffer_size, offset,
            "\n    {\n"
            "      \"pid\": %d,\n"
            "      \"name\": \"%s\",\n"
            "      \"state\": \"%c\",\n"
            "      \"memory\": %lu,\n"
            "      \"cpu\": %.1f,\n"
            "      \"command\": \"%s\"\n"
            "    }",
            p->pid, 
            safe_name,
            p->state,
            p->rss * 1024,
            p->cpu_usage, 
            safe_cmd);
        
        if (written > 0) {
            offset += written;
            processes_added++;
        }
        
        if (offset >= buffer_size - 100) {
            break;
        }
    }
    
    // Завершаем JSON
    if (buffer_size - offset >= 10) {
        strcpy(buffer + offset, "\n  ]\n}\n");
    } else {
        // Просто закрываем если мало места
        strncpy(buffer + buffer_size - 10, "\n]\n}\n", 10);
    }
    
    // Гарантируем что строка завершается нулем
    buffer[buffer_size - 1] = '\0';
    
    // Отладочный вывод - проверим последние 200 символов JSON
    printf("JSON generated, last 200 chars:\n");
    int len = strlen(buffer);
    int start = len > 200 ? len - 200 : 0;
    for (int i = start; i < len; i++) {
        unsigned char c = buffer[i];
        if (c < 32 || c == 127) {
            printf("[0x%02x]", c);
        } else {
            printf("%c", c);
        }
    }
    printf("\n");
}