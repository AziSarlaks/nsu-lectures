#include <stdio.h>
#include <string.h>

void reverse(char *start, int len) {
    for (int i = 0; i < len / 2; i++) {
        char temp = start[i];
        start[i] = start[len - 1 - i];
        start[len - 1 - i] = temp;
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n;
    char s[101];
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", s);
        reverse(s, strlen(s));
        printf("%s\n", s);
    }
}