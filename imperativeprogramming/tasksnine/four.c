#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b)
{
    int x = *(const int *)a;
    int y = *(const int *)b;
    return (x > y) - (x < y);
}

void print_int128(__int128_t n)
{
    if (n == 0)
    {
        printf("0");
        return;
    }
    char buf[40];
    int i = 0;
    int sign = n < 0;
    if (sign) n = -n;
    
    while (n > 0)
    {
        buf[i++] = '0' + (n % 10);
        n /= 10;
    }
    if (sign) printf("-");
    for (int j = i - 1; j >= 0; j--)
        putchar(buf[j]);
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    __int128_t s = 0;
    scanf("%d", &n);
    int *nums = malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++)
        scanf("%d", &nums[i]);

    qsort(nums, n, sizeof(int), cmp);
    
    for (int i = 0; i < n; i++)
    {
        s += (__int128_t)nums[i] * (n - 1 - i);
    }

    print_int128(s);
    free(nums);
    return 0;
}