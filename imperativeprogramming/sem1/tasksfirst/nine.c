#include <stdio.h>

int main() {
    freopen("input.txt", "r", stdin);
    long long maxsize = 0;
    long long count = 0;
    scanf("%lld", &maxsize);
    for (long long a = 1; a * a * a <= maxsize; a++) {
        for (long long b = a; a * b * b <= maxsize; b++) {
            long long max_c = maxsize / (a * b);
            if (max_c < b) {
                break;
            }
            count += max_c - b + 1;
        }
    }
    fclose(stdin);
    
    freopen("output.txt", "w", stdout);
    printf("%lld", count);
    fclose(stdout);
    return 0;
}