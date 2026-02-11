#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include "config.h"
#include "json_formatter.h"

// Функция для экранирования JSON строк (полная версия)
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
                // Управляющие символы (0x00-0x1F) должны быть экранированы как \uXXXX
                if (c < 32) {
                    // Экранируем как Unicode
                    if (j + 6 < max_len) {
                        snprintf(output + j, max_len - j, "\\u%04x", c);
                        j += 6;
                    }
                } else {
                    // Обычные символы
                    output[j++] = c;
                }
                break;
        }
        i++;
    }
    output[j] = '\0';
}

// Альтернативная упрощенная функция - заменяет проблемные символы
static void json_sanitize_string(const char *input, char *output, int max_len) {
    if (!input || !output || max_len <= 0) {
        if (output && max_len > 0) output[0] = '\0';
        return;
    }
    
    int i = 0, j = 0;
    
    while (input[i] && j < max_len - 1) {
        unsigned char c = (unsigned char)input[i];
        
        // Экранируем двойные кавычки и обратные слеши
        if (c == '"' || c == '\\') {
            if (j + 2 < max_len) {
                output[j++] = '\\';
                output[j++] = c;
            }
        }
        // Заменяем управляющие символы и непечатаемые символы на пробелы
        else if (c < 32 || c > 126) {
            output[j++] = ' ';
        }
        // Нормальные печатаемые символы
        else {
            output[j++] = c;
        }
        i++;
    }
    output[j] = '\0';
}

void format_system_info_json(char *buffer, int buffer_size, 
                            CPUStats *cpu, CPUStats *cores, int cores_count,
                            MemoryInfo *mem,
                            ProcessInfo *processes, int process_count) {
    time_t now = time(NULL);
    
    // Инициализируем буфер
    if (buffer_size < 1024) {
        snprintf(buffer, buffer_size, "{\"error\":\"buffer too small\"}");
        return;
    }
    
    buffer[0] = '{';
    buffer[1] = '\n';
    buffer[2] = '\0';
    
    int offset = 0;
    
    // Начинаем формировать JSON
    offset = snprintf(buffer, buffer_size,
        "{\n"
        "  \"timestamp\": %ld,\n"
        "  \"cpu\": {\n"
        "    \"usage\": %.1f,\n"
        "    \"cores_count\": %d,\n"
        "    \"cores\": [",
        now,
        cpu->usage_percent,
        cores_count);
    
    if (offset < 0 || offset >= buffer_size - 100) {
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
            if (offset + 1 < buffer_size) {
                buffer[offset++] = ',';
                buffer[offset] = '\0';
            }
        }
        
        int written = snprintf(buffer + offset, buffer_size - offset,
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
    int written = snprintf(buffer + offset, buffer_size - offset,
        "\n    ]\n"
        "  },\n"
        "  \"memory\": {\n"
        "    \"total\": %llu,\n"
        "    \"used\": %llu,\n"
        "    \"free\": %llu,\n"
        "    \"cached\": %llu,\n"
        "    \"percentage\": %.1f\n"
        "  },\n"
        "  \"processes\": [",
        mem->total, mem->used, mem->free, mem->cached, mem->percentage);
    
    if (written > 0) {
        offset += written;
    }
    
    if (offset >= buffer_size - 500) {
        // Закрываем JSON досрочно
        snprintf(buffer + offset, buffer_size - offset, "]\n}");
        return;
    }
    
    // Добавляем процессы (максимум 15 для безопасности)
    int limit = (process_count > 15) ? 15 : process_count;
    int processes_added = 0;
    
    for (int i = 0; i < limit; i++) {
        ProcessInfo *p = &processes[i];
        
        // Очищаем и экранируем строки
        char escaped_cmd[512];
        char escaped_name[256];
        
        // Используем упрощенную очистку
        json_sanitize_string(p->command_line, escaped_cmd, sizeof(escaped_cmd));
        json_sanitize_string(p->name, escaped_name, sizeof(escaped_name));
        
        // Если строки пустые после очистки, используем значения по умолчанию
        if (strlen(escaped_name) == 0) {
            strncpy(escaped_name, "unknown", sizeof(escaped_name) - 1);
            escaped_name[sizeof(escaped_name) - 1] = '\0';
        }
        
        if (strlen(escaped_cmd) == 0) {
            strncpy(escaped_cmd, escaped_name, sizeof(escaped_cmd) - 1);
            escaped_cmd[sizeof(escaped_cmd) - 1] = '\0';
        }
        
        // Проверяем, есть ли место
        if (buffer_size - offset < 600) {
            break;
        }
        
        // Добавляем запятую перед каждым процессом, кроме первого
        if (processes_added > 0) {
            buffer[offset++] = ',';
            buffer[offset] = '\0';
        }
        
        written = snprintf(buffer + offset, buffer_size - offset,
            "\n    {\n"
            "      \"pid\": %d,\n"
            "      \"name\": \"%s\",\n"
            "      \"state\": \"%c\",\n"
            "      \"memory\": %lu,\n"
            "      \"cpu\": %.1f,\n"
            "      \"command\": \"%s\"\n"
            "    }",
            p->pid, 
            escaped_name,
            p->state,
            p->rss * 1024,
            p->cpu_usage, 
            escaped_cmd);
        
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
        snprintf(buffer + offset, buffer_size - offset, "\n  ]\n}\n");
    } else {
        // Просто закрываем если мало места
        strncpy(buffer + buffer_size - 10, "\n]\n}\n", 10);
    }
    
    // Гарантируем что строка завершается нулем
    buffer[buffer_size - 1] = '\0';
}