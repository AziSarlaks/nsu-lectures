#include <stdio.h>
#include <stdlib.h>

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n;
    scanf("%d", &n);
    int nums[n];
    int sum = 0;
    int count = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
    }
    fclose(stdin);

    for (int k = 1; k <= n; k++) {
        sum = 0;
        for (int i = k-1; i < n; i+=k) {
            sum += nums[i];
        }
        if (k == n) {
            printf("%d", sum);
        } else {
            printf("%d\n", sum);
        }
    }

    fclose(stdout);
    return 0;
}