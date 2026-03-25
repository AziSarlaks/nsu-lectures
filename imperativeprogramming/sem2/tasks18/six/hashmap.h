#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdint.h>

#ifdef _WIN32
    #ifdef HASHMAP_EXPORTS
        #define HM_API __declspec(dllexport)
    #else
        #define HM_API __declspec(dllimport)
    #endif
#else
    #define HM_API __attribute__((visibility("default")))
#endif

typedef const void *cpvoid;

typedef int (*EqualFunc)(cpvoid a, cpvoid b);
typedef uint32_t (*HashFunc)(cpvoid key);

typedef struct Entry {
    cpvoid key;
    cpvoid value;
    int occupied;
} Entry;

typedef struct HashMap {
    Entry *entries;
    int size;
    int count;
    EqualFunc equal;
    HashFunc hash;
} HashMap;

HM_API HashMap HM_Init(EqualFunc ef, HashFunc hf, int size);
HM_API void HM_Destroy(HashMap *self);
HM_API cpvoid HM_Get(const HashMap *self, cpvoid key);
HM_API void HM_Set(HashMap *self, cpvoid key, cpvoid value);

#endif