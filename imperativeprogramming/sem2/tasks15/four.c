#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007LL

long long p;

long long inv(long long a)
{
    long long r = 1, b = p - 2;
    while (b)
    {
        if (b & 1)
            r = r * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return r;
}

int main()
{
    int n, k;
    if (scanf("%d%d%lld", &n, &k, &p) != 3)
        return 0;
    long long a[305][305] = {0}, b[305] = {0};
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < n; j++)
            scanf("%lld", &a[i][j]);
        scanf("%lld", &b[i]);
    }
    int row = 0, col = 0, rank = 0;
    while (row < k && col < n)
    {
        int sel = -1;
        for (int i = row; i < k; i++)
            if (a[i][col] % p)
            {
                sel = i;
                break;
            }
        if (sel == -1)
        {
            col++;
            continue;
        }
        for (int j = col; j < n; j++)
        {
            long long t = a[row][j];
            a[row][j] = a[sel][j];
            a[sel][j] = t;
        }
        long long tb = b[row];
        b[row] = b[sel];
        b[sel] = tb;
        long long iv = inv((a[row][col] % p + p) % p);
        for (int j = col; j < n; j++)
            a[row][j] = a[row][j] * iv % p;
        b[row] = b[row] * iv % p;
        for (int i = 0; i < k; i++)
            if (i != row && a[i][col] % p)
            {
                long long factor = a[i][col] % p;
                for (int j = col; j < n; j++)
                    a[i][j] = (a[i][j] - factor * a[row][j]) % p;
                b[i] = (b[i] - factor * b[row]) % p;
            }
        row++;
        col++;
        rank++;
    }
    for (int i = rank; i < k; i++)
    {
        int all0 = 1;
        for (int j = 0; j < n; j++)
            if (a[i][j] % p)
            {
                all0 = 0;
                break;
            }
        if (all0 && (b[i] % p + p) % p)
        {
            printf("0");
            return 0;
        }
    }
    if (rank == n)
    {
        long long x[305] = {0};
        printf("1\n");
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                if (a[i][j] % p)
                {
                    x[j] = (b[i] % p + p) % p;
                    break;
                }
        }
        for (int i = 0; i < n; i++)
            printf("%lld\n", x[i]);
    }
    else
    {
        long long cnt = 1;
        for (int i = 0; i < n - rank; i++)
            cnt = cnt * p % MOD;
        printf("%lld", cnt);
    }
    return 0;
}