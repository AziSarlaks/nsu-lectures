#include <stdio.h>

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n;
    scanf("%d", &n);
    int arr[100000];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    fclose(stdin);
    int max_sum = arr[0], cur_sum = arr[0];
    int l = 0, r = 0, temp_l = 0;

    for (int i = 1; i < n; i++) {
        if (cur_sum < 0) {
            cur_sum = arr[i];
            temp_l = i;
        } else {
            cur_sum += arr[i];
        }
        if (cur_sum > max_sum) {
            max_sum = cur_sum;
            l = temp_l;
            r = i;
        }
    }

    printf("%d %d %d\n", l, r, max_sum);
    fclose(stdout);
    return 0;
}