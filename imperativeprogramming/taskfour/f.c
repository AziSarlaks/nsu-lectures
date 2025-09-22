#include <stdio.h>
#include <stdlib.h>

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n;
    scanf("%d", &n);
    int nums[n];
    int sum = 0;
    int br, bl;
    int max = -10001;
    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
    }
    fclose(stdin);

    for (int i = 0; i < n; i++) {
        int r = nums[i];
        sum = 0;
        int tsum = 0;
        for (int li = i; li < n; i++) {
            int l = nums[li];
            if (sum+l > sum) {
                sum += l;
                bl = l;
                br = r;
            } else if (tsum > sum) {
                sum = tsum;
                bl = l;
                br = r;
            } else {
                tsum += l;
            }            
        }
    }

    fclose(stdout);
    return 0;
}
