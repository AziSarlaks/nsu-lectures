#include <stdio.h>
#include <stdlib.h>

void quicksort(int arr[], int left, int right) {
        if (left >= right) return;
        int p = arr[right];
        int i = left - 1;
        for (int j = left; j < right; j++) {
            if (arr[j] < p) {
                i++;
                int tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
        }
        int tmp = arr[i + 1];
        arr[i + 1] = arr[right];
        arr[right] = tmp;
        quicksort(arr, left, i);
        quicksort(arr, i + 2, right);
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n;
    scanf("%d", &n);
    int nums[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
    }
    
    fclose(stdin);
    quicksort(nums, 0, n - 1);

    int curr = nums[0];
    int count = 1;

    for (int i = 1; i <= n; i++) {
        if (nums[i] == curr) {
            count++;
        } else {
            if (i != n) {
                printf("%d: %d\n", curr, count);
            } else {
                printf("%d: %d", curr, count);
            }
            curr = nums[i];
            count = 1;
        }
    }
    fclose(stdout);
    return 0;
}