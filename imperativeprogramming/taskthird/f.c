#include <stdio.h>
#include <stdlib.h>

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n;
    scanf("%d", &n);
    int nums[n];
    int count = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
    }
    fclose(stdin);

    for (int i = 0; i < n; i++) {
        int bi = nums[i];
        count = 0;
        if (i == n-1) {
            printf("0");
            break;
        }
        for (int j = i + 1; j < n; j++) {
            int bj = nums[j];
            if (bi > bj) {
                count++;
            }
        }
        printf("%d ", count);
    }

    fclose(stdout);
    return 0;
}