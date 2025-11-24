#include <stdio.h>

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, k;
    scanf("%d %d", &n, &k);

    int l = 0;
    for (int i = 2; i <= n; i++) {
        l = (l + k) % i;
    }

    printf("%d\n", l + 1);

    return 0;
}