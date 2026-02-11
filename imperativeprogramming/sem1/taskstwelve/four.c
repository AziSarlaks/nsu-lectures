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

int compareActorBio(const void *a, const void *b)
{
    return strcmp(((ActorBio *)a)->name, ((ActorBio *)b)->name);
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

int findFirstMatch(ActorBio *arr, int n, const char *name)
{
    int left = 0, right = n - 1;
    int result = -1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        int cmp = strcmp(arr[mid].name, name);

        if (cmp == 0)
        {
            result = mid;
            right = mid - 1;
        }
        else if (cmp < 0)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }

    return result;
}

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

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int N, M;
    scanf("%d", &N);
    getchar();

    ActorBio *bios = (ActorBio *)malloc(N * sizeof(ActorBio));

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

    JoinedRecord *result = malloc(100005 * sizeof(JoinedRecord));
    int resultCount = 0;

    for (int i = 0; i < M; i++)
    {
        int idx = findFirstMatch(bios, N, movies[i].actorName);

        if (idx != -1)
        {
            int j = idx;
            while (j < N && strcmp(bios[j].name, movies[i].actorName) == 0)
            {
                result[resultCount].name = bios[j].name;
                result[resultCount].birthYear = bios[j].birthYear;
                result[resultCount].country = bios[j].country;
                result[resultCount].movieName = movies[i].movieName;
                resultCount++;
                j++;
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