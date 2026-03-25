#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json.h>

void write_int32(FILE *f, int32_t v) {
    fwrite(&v, 4, 1, f);
}

void write_double(FILE *f, double v) {
    fwrite(&v, 8, 1, f);
}

void write_byte(FILE *f, char v) {
    fwrite(&v, 1, 1, f);
}

void write_cstring(FILE *f, const char *s) {
    fwrite(s, 1, strlen(s) + 1, f);
}

void write_string(FILE *f, const char *s) {
    int32_t len = strlen(s) + 1;
    fwrite(&len, 4, 1, f);
    fwrite(s, 1, len, f);
}

void process_value(FILE *f, struct json_object *val, const char *key);

void process_array(FILE *f, struct json_object *arr) {
    long pos = ftell(f);
    int32_t zero = 0;
    fwrite(&zero, 4, 1, f);
    
    int len = json_object_array_length(arr);
    int i;
    for (i = 0; i < len; i++) {
        struct json_object *v = json_object_array_get_idx(arr, i);
        char key[20];
        sprintf(key, "%d", i);
        process_value(f, v, key);
    }
    
    write_byte(f, 0);
    
    long end = ftell(f);
    fseek(f, pos, SEEK_SET);
    int32_t size = end - pos;
    fwrite(&size, 4, 1, f);
    fseek(f, end, SEEK_SET);
}

void process_object(FILE *f, struct json_object *obj) {
    long pos = ftell(f);
    int32_t zero = 0;
    fwrite(&zero, 4, 1, f);
    
    json_object_object_foreach(obj, key, val) {
        process_value(f, val, key);
    }
    
    write_byte(f, 0);
    
    long end = ftell(f);
    fseek(f, pos, SEEK_SET);
    int32_t size = end - pos;
    fwrite(&size, 4, 1, f);
    fseek(f, end, SEEK_SET);
}

void process_value(FILE *f, struct json_object *val, const char *key) {
    int type = json_object_get_type(val);
    char t;
    
    switch (type) {
        case json_type_string: t = 2; break;
        case json_type_double: t = 1; break;
        case json_type_int: t = 1; break;
        case json_type_boolean: t = 8; break;
        case json_type_null: t = 10; break;
        case json_type_array: t = 4; break;
        case json_type_object: t = 3; break;
        default: return;
    }
    
    if (key) {
        write_byte(f, t);
        write_cstring(f, key);
    }
    
    switch (type) {
        case json_type_string:
            write_string(f, json_object_get_string(val));
            break;
        case json_type_double:
            write_double(f, json_object_get_double(val));
            break;
        case json_type_int:
            write_double(f, (double)json_object_get_int64(val));
            break;
        case json_type_boolean:
            write_byte(f, json_object_get_boolean(val) ? 1 : 0);
            break;
        case json_type_null:
            break;
        case json_type_array:
            process_array(f, val);
            break;
        case json_type_object:
            process_object(f, val);
            break;
    }
}

int main() {
    char *input = malloc(1000000);
    int pos = 0, c;
    
    while ((c = getchar()) != EOF) {
        input[pos++] = c;
    }
    input[pos] = '\0';
    
    struct json_object *root = json_tokener_parse(input);
    if (!root) {
        free(input);
        return 1;
    }
    
    int root_type = json_object_get_type(root);
    if (root_type == json_type_object) {
        process_object(stdout, root);
    } else if (root_type == json_type_array) {
        process_array(stdout, root);
    }
    
    json_object_put(root);
    free(input);
    return 0;
}