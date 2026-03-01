#include <stdio.h>

long long mp(long long a, long long pow, long long m)
{
    long long res = 1;
    while (pow > 0)
    {
        if (pow & 1)
        {
            res = (res * a) % m;
        }
        a = (a * a) % m;
        pow >>= 1;
    }
    return res;
}

int main()
{
    int T;
    long long M;
    scanf("%d %lld", &T, &M);

    while (T--)
    {
        long long A;
        scanf("%lld", &A);

        if (A % M == 0)
        {
            printf("-1\n");
        }
        else
        {
            long long inv = mp(A, M - 2, M);
            printf("%lld\n", inv);
        }
    }

    return 0;
}