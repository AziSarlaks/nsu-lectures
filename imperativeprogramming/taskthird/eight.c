#include <stdio.h>

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n;
    scanf("%d", &n);
    int height[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &height[i]);
    }

    int left_max[n], right_max[n];
    left_max[0] = height[0];
    for (int i = 1; i < n; i++) {
        if (height[i] > left_max[i-1]) {
            left_max[i] = height[i];
        } else {
            left_max[i] = left_max[i-1];
        }    
    }
    right_max[n-1] = height[n-1];
    for (int i = n-2; i >= 0; i--) {
        if (height[i] > right_max[i+1]) {
            right_max[i] = height[i];
        } else {
            right_max[i] = right_max[i+1];
        }    
    }

    long long water = 0;
    for (int i = 0; i < n; i++) {
        int min_lr;
        if (left_max[i] < right_max[i]) {
            min_lr = left_max[i];
        } else {
            min_lr = right_max[i];
        }        
        if (min_lr > height[i]) {
            water += min_lr - height[i];
        }
    }
    printf("%lld\n", water);
}