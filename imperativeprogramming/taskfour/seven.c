#include <stdio.h>
#include <string.h>

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int len = 0;
    char str[1001];
    if (fgets(str, 1001, stdin)) {
        char *p = str;
        while (*p) {
            while (*p == ' ') p++;
            if (!*p) break;

            char *s = p;
            len = 0;
            while (*p && *p != ' ') {
                len++;
                p++;
            }
            if (len == 1) {
                printf("%c ", *s);
            } else if (len == 2) {
                printf("%c0%c ", *s, *(s + 1));
            } else if (len > 2) {
                printf("%c%d%c ", *s, len - 2, *(s + len - 1));
            }
        }
    }
}