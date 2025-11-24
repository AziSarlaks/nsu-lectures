#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b)
{
    long long x = *(const long long *)a;
    long long y = *(const long long *)b;
    return (x > y) - (x < y);
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    scanf("%d", &n);

    long long *a = malloc(sizeof(long long) * n);
    for (int i = 0; i < n; i++)
        scanf("%lld", &a[i]);

    qsort(a, n, sizeof(long long), cmp);

    int k = 0;
    for (int i = 0; i < n; i++)
        if (i == 0 || a[i] != a[i - 1])
            a[k++] = a[i];

    printf("%d\n", k);
    for (int i = 0; i < k; i++)
        printf("%lld\n", a[i]);

    free(a);
}