#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char value[8];
} Record;

typedef struct {
    Record* data;
    int size;
    int capacity;
} DA;

void init_array(DA* arr) {
    arr->capacity = 4;
    arr->size = 0;
    arr->data = malloc(arr->capacity * sizeof(Record));
}

void push_back(DA* arr, const char* value) {
    if (arr->size >= arr->capacity) {
        arr->capacity *= 2;
        arr->data = realloc(arr->data, arr->capacity * sizeof(Record));
    }
    strcpy(arr->data[arr->size].value, value);
    arr->size++;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int N;
    scanf("%d", &N);

    DA* arrays = (DA*)malloc((1000000 + 1) * sizeof(DA));
    
    for (int i = 0; i <= 1000000; i++) {
        init_array(&arrays[i]);
    }

    for (int i = 0; i < N; i++) {
        int key;
        char value[8];
        scanf("%d %s", &key, value);
        
        if (key >= 0 && key <= 1000000) {
            push_back(&arrays[key], value);
        }
    }

    for (int key = 0; key <= 1000000; key++) {
        DA* arr = &arrays[key];
        for (int i = 0; i < arr->size; i++) {
            printf("%d %s\n", key, arr->data[i].value);
        }
    }

    for (int i = 0; i <= 1000000; i++) {
        free(arrays[i].data);
    }
    free(arrays);

    return 0;
}