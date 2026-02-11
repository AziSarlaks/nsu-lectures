#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct
{
    uint32_t key;
    uint32_t hash;
    int used;
} HashEntry;

HashEntry hashTable[200003];

unsigned int hash_func(uint32_t x)
{
    return x % 200003;
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    uint32_t x;
    char command[10];

    for (uint32_t i = 1; i <= 100000; i++)
    {
        printf("eval %u\n", i);
        fflush(stdout);

        scanf("%u", &x);

        unsigned int idx = hash_func(x);

        while (hashTable[idx].used)
        {
            if (hashTable[idx].hash == x)
            {
                printf("answer %u %u\n", hashTable[idx].key, i);
                fflush(stdout);
                return 0;
            }
            idx = (idx + 1) % 200003;
        }

        hashTable[idx].key = i;
        hashTable[idx].hash = x;
        hashTable[idx].used = 1;
    }

    return 0;
}