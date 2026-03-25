#include "hashmap.h"
#include <stdlib.h>
#include <string.h>

HM_API HashMap HM_Init(EqualFunc ef, HashFunc hf, int size) {
    HashMap map;
    map.entries = calloc(size, sizeof(Entry));
    map.size = size;
    map.count = 0;
    map.equal = ef;
    map.hash = hf;
    return map;
}

HM_API void HM_Destroy(HashMap *self) {
    if (!self) return;
    if (self->entries) {
        free(self->entries);
        self->entries = NULL;
    }
}

HM_API cpvoid HM_Get(const HashMap *self, cpvoid key) {
    if (!self || !self->entries) return NULL;
    
    uint32_t h = self->hash(key);
    int idx = h % self->size;
    
    for (int i = 0; i < self->size; i++) {
        int probe = (idx + i) % self->size;
        Entry *e = &self->entries[probe];
        
        if (!e->occupied) {
            return NULL;
        }
        
        if (self->equal(e->key, key)) {
            return e->value;
        }
    }
    
    return NULL;
}

HM_API void HM_Set(HashMap *self, cpvoid key, cpvoid value) {
    if (!self || !self->entries) return;
    
    uint32_t h = self->hash(key);
    int idx = h % self->size;
    int first_free = -1;
    
    for (int i = 0; i < self->size; i++) {
        int probe = (idx + i) % self->size;
        Entry *e = &self->entries[probe];
        
        if (!e->occupied) {
            if (first_free == -1) {
                first_free = probe;
            }
            break;
        }
        
        if (self->equal(e->key, key)) {
            e->value = value;
            return;
        }
    }
    
    if (first_free != -1) {
        Entry *e = &self->entries[first_free];
        e->key = key;
        e->value = value;
        e->occupied = 1;
        self->count++;
    }
}