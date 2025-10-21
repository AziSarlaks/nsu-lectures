#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// Функции для чтения little-endian данных
int32_t read_int32(const uint8_t *data) {
    return (int32_t)data[0] | ((int32_t)data[1] << 8) | 
           ((int32_t)data[2] << 16) | ((int32_t)data[3] << 24);
}

int64_t read_int64(const uint8_t *data) {
    return (int64_t)data[0] | ((int64_t)data[1] << 8) | 
           ((int64_t)data[2] << 16) | ((int64_t)data[3] << 24) |
           ((int64_t)data[4] << 32) | ((int64_t)data[5] << 40) | 
           ((int64_t)data[6] << 48) | ((int64_t)data[7] << 56);
}

double read_double(const uint8_t *data) {
    double result;
    memcpy(&result, data, sizeof(double));
    return result;
}

typedef struct {
    char *name;
    int type;
    union {
        double d_val;
        int32_t i32_val;
        int64_t i64_val;
        char *str_val;
        int bool_val;
    } value;
} Field;

int main() {
    FILE *input = fopen("input.txt", "rb");
    if (!input) {
        fprintf(stderr, "Cannot open input.txt\n");
        return 1;
    }
    
    // Определяем размер файла
    fseek(input, 0, SEEK_END);
    long file_size = ftell(input);
    fseek(input, 0, SEEK_SET);
    
    // Читаем весь файл
    uint8_t *buffer = (uint8_t*)malloc(file_size);
    if (!buffer) {
        fclose(input);
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    if (fread(buffer, 1, file_size, input) != (size_t)file_size) {
        free(buffer);
        fclose(input);
        fprintf(stderr, "Failed to read file\n");
        return 1;
    }
    fclose(input);
    
    // Читаем общий размер документа
    int32_t total_size = read_int32(buffer);
    if (total_size > file_size) {
        free(buffer);
        fprintf(stderr, "Invalid BSON size\n");
        return 1;
    }
    int pos = 4; // Пропускаем размер
    
    Field *fields = NULL;
    int field_count = 0;
    int capacity = 10;
    fields = (Field*)malloc(capacity * sizeof(Field));
    if (!fields) {
        free(buffer);
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    // Парсим поля до конца документа
    while (pos < total_size - 1) {
        // Читаем тип поля
        uint8_t field_type = buffer[pos++];
        if (field_type == 0) break;
        
        // Читаем имя поля (до нулевого байта)
        int name_start = pos;
        while (pos < total_size && buffer[pos] != 0) {
            pos++;
        }
        if (pos >= total_size || buffer[pos] != 0) {
            // Cleanup
            for (int i = 0; i < field_count; i++) {
                free(fields[i].name);
                if (fields[i].type == 2) free(fields[i].value.str_val);
            }
            free(fields);
            free(buffer);
            fprintf(stderr, "Invalid field name\n");
            return 1;
        }
        
        int name_len = pos - name_start;
        char *field_name = (char*)malloc(name_len + 1);
        if (!field_name) {
            // Cleanup
            for (int i = 0; i < field_count; i++) {
                free(fields[i].name);
                if (fields[i].type == 2) free(fields[i].value.str_val);
            }
            free(fields);
            free(buffer);
            fprintf(stderr, "Memory allocation failed\n");
            return 1;
        }
        memcpy(field_name, buffer + name_start, name_len);
        field_name[name_len] = '\0';
        pos++; // Пропускаем нулевой байт
        
        // Обрабатываем значение в зависимости от типа
        Field field;
        field.name = field_name;
        field.type = field_type;
        
        switch (field_type) {
            case 1: { // double
                if (pos + 8 > total_size) goto error;
                field.value.d_val = read_double(buffer + pos);
                pos += 8;
                break;
            }
            case 2: { // string
                if (pos + 4 > total_size) goto error;
                int32_t str_size = read_int32(buffer + pos);
                pos += 4;
                if (str_size <= 0 || pos + str_size > total_size) goto error;
                // Выделяем память для строки (str_size -1 chars + \0)
                field.value.str_val = (char*)malloc(str_size);
                if (!field.value.str_val) goto error_mem;
                memcpy(field.value.str_val, buffer + pos, str_size - 1);
                field.value.str_val[str_size - 1] = '\0';
                pos += str_size; // str_size уже включает нулевой байт
                break;
            }
            case 8: { // bool
                if (pos + 1 > total_size) goto error;
                field.value.bool_val = buffer[pos];
                pos += 1;
                break;
            }
            case 10: { // null
                // Нет данных для чтения
                break;
            }
            case 16: { // int32
                if (pos + 4 > total_size) goto error;
                field.value.i32_val = read_int32(buffer + pos);
                pos += 4;
                break;
            }
            case 18: { // int64
                if (pos + 8 > total_size) goto error;
                field.value.i64_val = read_int64(buffer + pos);
                pos += 8;
                break;
            }
            default:
                fprintf(stderr, "Unknown type %d\n", field_type);
                goto error;
        }
        
        // Добавляем поле в массив
        if (field_count >= capacity) {
            capacity *= 2;
            Field *new_fields = (Field*)realloc(fields, capacity * sizeof(Field));
            if (!new_fields) goto error_mem;
            fields = new_fields;
        }
        fields[field_count++] = field;
    }
    
    if (pos != total_size) {
        fprintf(stderr, "Parse error: pos %d != total %d\n", pos, total_size);
        goto error;
    }
    
    // Выводим JSON
    FILE *output = fopen("output.txt", "w");
    if (!output) {
        fprintf(stderr, "Cannot create output.txt\n");
        goto error;
    }
    
    fprintf(output, "{\n");
    for (int i = 0; i < field_count; i++) {
        Field *field = &fields[i];
        
        // Выводим имя поля
        fprintf(output, "  \"%s\": ", field->name);
        
        // Выводим значение в зависимости от типа
        switch (field->type) {
            case 1: // double
                fprintf(output, "%0.15g", field->value.d_val);
                break;
            case 2: // string
                fprintf(output, "\"%s\"", field->value.str_val);
                break;
            case 8: // bool
                fprintf(output, "%s", field->value.bool_val ? "true" : "false");
                break;
            case 10: // null
                fprintf(output, "null");
                break;
            case 16: // int32
                fprintf(output, "%d", field->value.i32_val);
                break;
            case 18: // int64
                fprintf(output, "%lld", field->value.i64_val);
                break;
        }
        
        // Запятая для всех кроме последнего поля
        if (i < field_count - 1) {
            fprintf(output, ",");
        }
        fprintf(output, "\n");
    }
    fprintf(output, "}\n");
    fclose(output);
    
    // Освобождаем память
    for (int i = 0; i < field_count; i++) {
        free(fields[i].name);
        if (fields[i].type == 2) {
            free(fields[i].value.str_val);
        }
    }
    free(fields);
    free(buffer);
    
    return 0;

error_mem:
    fprintf(stderr, "Memory allocation failed\n");

error:
    // Cleanup
    for (int i = 0; i < field_count; i++) {
        free(fields[i].name);
        if (fields[i].type == 2) free(fields[i].value.str_val);
    }
    free(fields);
    free(buffer);
    return 1;
}