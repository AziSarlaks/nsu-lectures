#if defined(NAME) && defined(TYPE)

#define CONCAT_IMPL(x, y) x##y
#define CONCAT(x, y) CONCAT_IMPL(x, y)

#include <stdlib.h>
#include <string.h>

void CONCAT(NAME, _init)(CONCAT(NAME, _s) *vec) {
    vec->n = 0;
    vec->arr = NULL;
    vec->capacity = 0;
}

void CONCAT(NAME, _destroy)(CONCAT(NAME, _s) *vec) {
    if (vec->arr) {
        free(vec->arr);
        vec->arr = NULL;
    }
    vec->n = 0;
    vec->capacity = 0;
}

int CONCAT(NAME, _push)(CONCAT(NAME, _s) *vec, TYPE value) {
    if (vec->n >= vec->capacity) {
        int new_capacity = vec->capacity == 0 ? 4 : vec->capacity * 2;
        TYPE *new_arr = (TYPE*)realloc(vec->arr, new_capacity * sizeof(TYPE));
        if (!new_arr) return -1;
        vec->arr = new_arr;
        vec->capacity = new_capacity;
    }
    vec->arr[vec->n] = value;
    vec->n++;
    return vec->n - 1;
}

TYPE CONCAT(NAME, _pop)(CONCAT(NAME, _s) *vec) {
    if (vec->n > 0) {
        vec->n--;
        return vec->arr[vec->n];
    }
    return (TYPE)0;
}

void CONCAT(NAME, _reserve)(CONCAT(NAME, _s) *vec, int capacity) {
    if (capacity > vec->capacity) {
        TYPE *new_arr = (TYPE*)realloc(vec->arr, capacity * sizeof(TYPE));
        if (new_arr) {
            vec->arr = new_arr;
            vec->capacity = capacity;
        }
    }
}

void CONCAT(NAME, _resize)(CONCAT(NAME, _s) *vec, int newCnt, TYPE fill) {
    if (newCnt > vec->capacity) {
        CONCAT(NAME, _reserve)(vec, newCnt);
    }
    if (newCnt > vec->n) {
        for (int i = vec->n; i < newCnt; i++) {
            vec->arr[i] = fill;
        }
    }
    vec->n = newCnt;
}

void CONCAT(NAME, _insert)(CONCAT(NAME, _s) *vec, int where, const TYPE *arr, int num) {
    if (num <= 0 || where < 0 || where > vec->n) return;
    
    if (vec->n + num > vec->capacity) {
        int new_capacity = vec->n + num;
        if (new_capacity < vec->capacity * 2) {
            new_capacity = vec->capacity * 2;
        }
        CONCAT(NAME, _reserve)(vec, new_capacity);
    }
    
    for (int i = vec->n - 1; i >= where; i--) {
        vec->arr[i + num] = vec->arr[i];
    }
    
    for (int i = 0; i < num; i++) {
        vec->arr[where + i] = arr[i];
    }
    
    vec->n += num;
}

void CONCAT(NAME, _erase)(CONCAT(NAME, _s) *vec, int where, int num) {
    if (num <= 0 || where < 0 || where >= vec->n) return;
    
    if (where + num > vec->n) {
        num = vec->n - where;
    }
    
    for (int i = where + num; i < vec->n; i++) {
        vec->arr[i - num] = vec->arr[i];
    }
    
    vec->n -= num;
}

#endif