#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct BioNode
{
    char name[31];
    int birthYear;
    char country[11];
    struct BioNode *next;
} BioNode;

typedef struct
{
    char actorName[31];
    char movieName[21];
} MovieRecord;

BioNode *hashTable[200003];

unsigned int hash(const char *str)
{
    unsigned int h = 0;
    for (int i = 0; str[i]; i++)
    {
        h = h * 31 + (unsigned char)str[i];
    }
    return h % 200003;
}

void addToHash(const char *name, int birthYear, const char *country)
{
    unsigned int h = hash(name);
    BioNode *node = malloc(sizeof(BioNode));
    strcpy(node->name, name);
    node->birthYear = birthYear;
    strcpy(node->country, country);
    node->next = hashTable[h];
    hashTable[h] = node;
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, m;
    scanf("%d\n", &n);

    for (int i = 0; i < n; i++)
    {
        char name[100], country[100];
        int birthYear;
        scanf("\"%[^\"]\" %d \"%[^\"]\"\n", name, &birthYear, country);
        addToHash(name, birthYear, country);
    }

    scanf("%d\n", &m);

    MovieRecord *movies = malloc(m * sizeof(MovieRecord));
    for (int i = 0; i < m; i++)
    {
        char actorName[100], movieName[100];
        scanf("\"%[^\"]\" \"%[^\"]\"\n", actorName, movieName);
        strcpy(movies[i].actorName, actorName);
        strcpy(movies[i].movieName, movieName);
    }

    for (int i = 0; i < m; i++)
    {
        unsigned int h = hash(movies[i].actorName);
        BioNode *node = hashTable[h];

        while (node != NULL)
        {
            if (strcmp(node->name, movies[i].actorName) == 0)
            {
                printf("\"%s\" %d \"%s\" \"%s\" \"%s\"\n",
                       node->name, node->birthYear, node->country,
                       movies[i].actorName, movies[i].movieName);
            }
            node = node->next;
        }
    }

    for (int i = 0; i < 200003; i++)
    {
        BioNode *node = hashTable[i];
        while (node != NULL)
        {
            BioNode *temp = node;
            node = node->next;
            free(temp);
        }
    }

    free(movies);

    return 0;
}