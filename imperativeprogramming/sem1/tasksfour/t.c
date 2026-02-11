#include <stdio.h>

char *concat(char *pref, char *suff) {
    static char buf[10001];
    snprintf(buf, sizeof(buf), "%s%s", pref, suff);
    return buf;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n;
    scanf("%d", &n);
    char pref[101];
    char suff[101];
    scanf("%s", pref);
    scanf("%s", suff);
    char *res = concat(pref, suff);
    for (int i = 2; i < n; i++) {
        scanf("%s", suff);
        char temp[10001];
        snprintf(temp, sizeof(temp), "%s", res);
        res = concat(temp, suff);
    }
    printf("%s", res);
    fclose(stdin);
    fclose(stdout);
}