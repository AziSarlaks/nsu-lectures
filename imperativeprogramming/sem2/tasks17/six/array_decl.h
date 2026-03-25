#ifndef ARRAY_DECL_H_
#define ARRAY_DECL_H_

#if defined(NAME) && defined(TYPE)

#define CONCAT_IMPL(x, y) x##y
#define CONCAT(x, y) CONCAT_IMPL(x, y)

typedef struct {
    int n;
    TYPE *arr;
    int capacity;
} CONCAT(NAME, _s);

void CONCAT(NAME, _init)(CONCAT(NAME, _s) *vec);
void CONCAT(NAME, _destroy)(CONCAT(NAME, _s) *vec);
int CONCAT(NAME, _push)(CONCAT(NAME, _s) *vec, TYPE value);
TYPE CONCAT(NAME, _pop)(CONCAT(NAME, _s) *vec);
void CONCAT(NAME, _reserve)(CONCAT(NAME, _s) *vec, int capacity);
void CONCAT(NAME, _resize)(CONCAT(NAME, _s) *vec, int newCnt, TYPE fill);
void CONCAT(NAME, _insert)(CONCAT(NAME, _s) *vec, int where, const TYPE *arr, int num);
void CONCAT(NAME, _erase)(CONCAT(NAME, _s) *vec, int where, int num);

#endif

#endif