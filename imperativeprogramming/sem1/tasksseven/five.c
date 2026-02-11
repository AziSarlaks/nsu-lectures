#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Tokens_s
{
    int num;
    char **arr;
} Tokens;

void tokensSplit(Tokens *tokens, const char *str, const char *delims)
{
    char *token = strtok(strdup(str), delims);
    int count = 0;

    while (token)
    {
        if (token[0] != '\0' && token[0] != ' ' && token[0] != '\n' && token[0] != '\r')
        {
            count++;
        }
        token = strtok(NULL, delims);
    }
    tokens->num = count;

    if (!tokens->arr)
    {
        return;
    }

    token = strtok(strdup(str), delims);
    int i = 0;

    while (token)
    {
        if (token[0] != '\0' && token[0] != ' ' && token[0] != '\n' && token[0] != '\r')
        {
            tokens->arr[i++] = strdup(token);
        }
        token = strtok(NULL, delims);
    }
}

void tokensFree(Tokens *tokens)
{
    if (tokens->arr && tokens->num != 0)
    {
        for (int i = 0; i < tokens->num; i++)
        {
            free(tokens->arr[i]);
        }
        free(tokens->arr);
    }
    tokens->arr = NULL;
    tokens->num = 0;
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    char delims[] = ".,:;";
    char str[1000001];

    fgets(str, sizeof(str), stdin);
    Tokens tokens = {0, NULL};

    tokensSplit(&tokens, str, delims);
    tokens.arr = malloc(tokens.num * sizeof(char *));
    tokensSplit(&tokens, str, delims);

    printf("%d\n", tokens.num);
    for (int i = 0; i < tokens.num; i++)
    {
        printf("%s\n", tokens.arr[i]);
    }

    tokensFree(&tokens);

    fclose(stdin);
    fclose(stdout);
}