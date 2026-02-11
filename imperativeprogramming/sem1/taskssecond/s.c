#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    char s[7];
    scanf("%s", s);
    fclose(stdin);
    int r = 0, g = 0, b = 0;
    int f = 0;
    char isx[] = "GHIJKLMNOPQRSTUVWXYZghijklmnopqrstuvwxyz";
    for (int i = 0; i < 6; i++) {
        if (strchr(isx, s[i]) != NULL) {
            f = 1;
            break;
        }
    }
    if (strlen(s) == 6 && f == 0) {
        r = strtol((const char[]){s[0], s[1], '\0'}, NULL, 16);
        g = strtol((const char[]){s[2], s[3], '\0'}, NULL, 16);
        b = strtol((const char[]){s[4], s[5], '\0'}, NULL, 16);
        printf("%d %d %d", r, g, b);
    } else {
        printf("-1 -1 -1");
    }
    fclose(stdout);
    return 0;
}