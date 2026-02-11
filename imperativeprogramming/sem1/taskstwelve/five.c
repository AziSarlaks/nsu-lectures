#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 35
#define MAX_COUNTRY_LEN 15
#define MAX_MOVIE_LEN 25

typedef struct
{
    char *name;
    int birthYear;
    char *country;
} ActorBio;

typedef struct
{
    char *actorName;
    char *movieName;
} ActorInMovie;

typedef struct
{
    char *name;
    int birthYear;
    char *country;
    char *movieName;
} JoinedRecord;

char *readQuotedString(char **ptr)
{
    char *start = strchr(*ptr, '"');
    if (!start)
        return NULL;

    start++;
    char *end = strchr(start, '"');
    if (!end)
        return NULL;

    int len = end - start;
    char *result = malloc(len + 1);
    strncpy(result, start, len);
    result[len] = '\0';

    *ptr = end + 1;
    return result;
}

int compareActorBio(const void *a, const void *b)
{
    return strcmp(((ActorBio *)a)->name, ((ActorBio *)b)->name);
}

int compareActorInMovie(const void *a, const void *b)
{
    return strcmp(((ActorInMovie *)a)->actorName, ((ActorInMovie *)b)->actorName);
}

int compareJoined(const void *a, const void *b)
{
    JoinedRecord *ja = (JoinedRecord *)a;
    JoinedRecord *jb = (JoinedRecord *)b;

    int nameCmp = strcmp(ja->name, jb->name);
    if (nameCmp != 0)
        return nameCmp;
    return ja->birthYear - jb->birthYear;
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int N, M;
    scanf("%d", &N);
    getchar();

    ActorBio *bios = malloc(N * sizeof(ActorBio));

    for (int i = 0; i < N; i++)
    {
        char line[200];
        fgets(line, sizeof(line), stdin);

        char *ptr = line;
        bios[i].name = readQuotedString(&ptr);
        bios[i].birthYear = atoi(ptr);

        while (*ptr && (*ptr < '0' || *ptr > '9'))
            ptr++;
        while (*ptr && (*ptr >= '0' && *ptr <= '9'))
            ptr++;

        bios[i].country = readQuotedString(&ptr);
    }

    scanf("%d", &M);
    getchar();

    ActorInMovie *movies = malloc(M * sizeof(ActorInMovie));

    for (int i = 0; i < M; i++)
    {
        char line[200];
        fgets(line, sizeof(line), stdin);

        char *ptr = line;
        movies[i].actorName = readQuotedString(&ptr);
        movies[i].movieName = readQuotedString(&ptr);
    }

    qsort(bios, N, sizeof(ActorBio), compareActorBio);
    qsort(movies, M, sizeof(ActorInMovie), compareActorInMovie);

    JoinedRecord *result = malloc(100005 * sizeof(JoinedRecord));
    int resultCount = 0;

    int i = 0, j = 0;

    while (i < N && j < M)
    {
        int cmp = strcmp(bios[i].name, movies[j].actorName);

        if (cmp < 0)
        {
            i++;
        }
        else if (cmp > 0)
        {
            j++;
        }
        else
        {
            int start_i = i;
            int start_j = j;

            while (i < N && strcmp(bios[i].name, movies[j].actorName) == 0)
            {
                i++;
            }

            while (j < M && strcmp(bios[start_i].name, movies[j].actorName) == 0)
            {
                j++;
            }

            for (int k = start_i; k < i; k++)
            {
                for (int l = start_j; l < j; l++)
                {
                    result[resultCount].name = bios[k].name;
                    result[resultCount].birthYear = bios[k].birthYear;
                    result[resultCount].country = bios[k].country;
                    result[resultCount].movieName = movies[l].movieName;
                    resultCount++;
                }
            }
        }
    }

    qsort(result, resultCount, sizeof(JoinedRecord), compareJoined);

    for (int i = 0; i < resultCount; i++)
    {
        printf("\"%s\" %d \"%s\" \"%s\" \"%s\"\n",
               result[i].name,
               result[i].birthYear,
               result[i].country,
               result[i].name,
               result[i].movieName);
    }

    for (int i = 0; i < N; i++)
    {
        free(bios[i].name);
        free(bios[i].country);
    }
    free(bios);

    for (int i = 0; i < M; i++)
    {
        free(movies[i].actorName);
        free(movies[i].movieName);
    }
    free(movies);

    free(result);

    return 0;
}