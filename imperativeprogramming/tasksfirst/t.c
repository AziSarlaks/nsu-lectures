#include <stdio.h>
#include <string.h>

int ninescount(const char* s, int len) {
    int sum = 0;
    for (int i = 0; i < len; i++) {
        if (s[i] == '9') sum++;
    }
    return sum;
}

int zerocount(int len) {
    int sum = 0;
    for (int i = len - 1; i >= 0; i--) {
        if (s[i] == '0') sum++;
        else break;
    }
    return sum;
}

int main() {
    freopen("input.txt", "r", stdin);
    int n, sum = 0;
    scanf("%d", &n);
    char c[101];
    for (int i = 0; i < n; i++) {
        scanf("%100s", c);
        int len = strlen(c);
        int ninesf = ninescount(c, len);
        if (c[len - 1] == '0') {
            int zeros = zerocount(c, len);
            if (c[len - 1 - zeros] == '9') {
                sum += zerocount(c, len) + 1;
            } else {
                sum += zerocount(c, len) + 2;
            }
        } else if (c[len - 1] == '9') {
            sum += 1;
        } else {
            sum += 2;
        }
    }
    fclose(stdin);
    freopen("output.txt", "w", stdout);
    printf("%d", sum);
    fclose(stdout);
    return 0;
}

