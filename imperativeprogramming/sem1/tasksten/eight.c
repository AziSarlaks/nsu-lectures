#include <stdio.h>
#include <limits.h>

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    int k, n = 0;
    scanf("%d", &k);
    
    int nums[100000];
    while (scanf("%d", &nums[n]) != EOF) n++;
    
    long long dp[100000];
    dp[0] = nums[0];
    
    int deque[100000];
    int front = 0, back = 0;
    deque[back++] = 0;
    
    for (int i = 1; i < n; i++) {
        while (front < back && deque[front] < i - k) front++;
        
        dp[i] = dp[deque[front]] + nums[i];
        
        while (front < back && dp[deque[back - 1]] <= dp[i]) back--;
        deque[back++] = i;
    }
    
    printf("%lld\n", dp[n - 1]);
    
    return 0;
}