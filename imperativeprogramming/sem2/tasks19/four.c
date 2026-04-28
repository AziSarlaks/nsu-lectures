#include <stdio.h>
#include <stdlib.h>

#define MAX_N 500

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int N;
    scanf("%d", &N);

    int R[MAX_N][MAX_N];

    for (int i = 0; i < N; i++)
    {
        char line[MAX_N + 1];
        scanf("%s", line);
        for (int j = 0; j < N; j++)
        {
            R[i][j] = line[j] - '0';
        }
    }

    for (int i = 0; i < N; i++)
    {
        R[i][i] = 1;
    }

    for (int k = 0; k < N; k++)
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (R[i][k] && R[k][j])
                {
                    R[i][j] = 1;
                }
            }
        }
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%d", R[i][j]);
        }
        printf("\n");
    }

    return 0;
}