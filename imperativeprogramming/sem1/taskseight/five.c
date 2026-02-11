#include <stdio.h>
#include <stdlib.h>

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int N, Q;
    scanf("%d", &N);
    long long *arr = malloc(sizeof(long long) * N);
    for (int i = 0; i < N; ++i)
        scanf("%lld", &arr[i]);
    scanf("%d", &Q);
    while (Q--)
    {
        long long y;
        scanf("%lld", &y);

        int l = 0, r = N;
        while (l < r)
        {
            int m = (l + r) >> 1;
            if (arr[m] < y)
                l = m + 1;
            else
                r = m;
        }
        int p = l;

        int idx;
        long long d;
        if (p == 0)
        {
            idx = 0;
            d = llabs(arr[0] - y);
        }
        else if (p == N)
        {
            idx = N - 1;
            d = llabs(arr[N - 1] - y);
        }
        else
        {
            long long dR = llabs(arr[p] - y);
            long long dL = llabs(arr[p - 1] - y);
            if (dR < dL)
            {
                idx = p;
                d = dR;
            }
            else if (dL < dR)
            {
                idx = p - 1;
                d = dL;
            }
            else
            {
                idx = p;
                d = dR;
            }
        }
        printf("%d %lld\n", idx, d);
    }

    free(arr);
    fclose(stdin);
    fclose(stdout);
    return 0;
}