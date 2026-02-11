#include <stdio.h>
#include <stdlib.h>

int main()
{
    int M, T;
    scanf("%d %d", &M, &T);

    int **C = malloc((2000 + 1) * sizeof(int *));
    for (int i = 0; i <= 2000; i++)
    {
        C[i] = malloc((i + 1) * sizeof(int));
    }

    for (int n = 0; n <= 2000; n++)
    {
        C[n][0] = 1 % M;
        C[n][n] = 1 % M;
        for (int k = 1; k < n; k++)
        {
            C[n][k] = (C[n - 1][k - 1] + C[n - 1][k]) % M;
        }
    }

    while (T--)
    {
        int N, K;
        scanf("%d %d", &N, &K);

        if (K < 0 || K > N)
        {
            printf("0\n");
        }
        else
        {
            printf("%d\n", C[N][K]);
        }
    }

    for (int i = 0; i <= 2000; i++)
    {
        free(C[i]);
    }
    free(C);

    return 0;
}