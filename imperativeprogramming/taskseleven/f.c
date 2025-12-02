#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 1000003
#define EMPTY -2147483648

typedef struct
{
    int key;
    int value;
} Entry;

int hash(int key)
{
    return (key % TABLE_SIZE + TABLE_SIZE) % TABLE_SIZE;
}

int main()
{
    freopen("input.txt", "rb", stdin);
    freopen("output.txt", "wb", stdout);

    int n;
    fread(&n, sizeof(int), 1, stdin);

    Entry *hashTable = calloc(TABLE_SIZE, sizeof(Entry));
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        hashTable[i].key = EMPTY;
    }

    int *result = malloc(n * sizeof(int));
    int count = 0;

    for (int i = 0; i < n; i++)
    {
        int num;
        fread(&num, sizeof(int), 1, stdin);

        int index = hash(num);
        int found = 0;

        while (hashTable[index].key != EMPTY)
        {
            if (hashTable[index].key == num)
            {
                found = 1;
                break;
            }
            index = (index + 1) % TABLE_SIZE;
        }

        if (!found)
        {
            result[count++] = num;
            hashTable[index].key = num;
            hashTable[index].value = 1;
        }
    }

    fwrite(&count, sizeof(int), 1, stdout);
    fwrite(result, sizeof(int), count, stdout);

    free(hashTable);
    free(result);

    return 0;
}