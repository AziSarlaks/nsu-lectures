#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define TABLE_SIZE 4000007
#define EMPTY UINT64_MAX

typedef struct {
    uint64_t key;
    int index;
} HashEntry;

uint64_t M, a, b, c;

uint64_t func(uint64_t s) {
    return (s * s * a + s * b + c) % M;
}

int hash(uint64_t key) {
    return (key % TABLE_SIZE + TABLE_SIZE) % TABLE_SIZE;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    scanf("%llu", &M);
    scanf("%llu %llu %llu", &a, &b, &c);
    
    HashEntry *hashTable = (HashEntry*)calloc(TABLE_SIZE, sizeof(HashEntry));
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i].key = EMPTY;
        hashTable[i].index = -1;
    }
    
    uint64_t state = 1;
    int l = -1, r = -1;
    int found = 0;
    
    for (int i = 0; i <= 2000000 && !found; i++) {
        int idx = hash(state);
        while (hashTable[idx].key != EMPTY) {
            if (hashTable[idx].key == state) {
                l = hashTable[idx].index;
                r = i - 1;
                found = 1;
                break;
            }
            idx = (idx + 1) % TABLE_SIZE;
        }
        
        if (found) break;
        
        hashTable[idx].key = state;
        hashTable[idx].index = i;
        
        state = func(state);
    }
    
    printf("%d %d\n", l, r+1);
    
    free(hashTable);
    return 0;
}