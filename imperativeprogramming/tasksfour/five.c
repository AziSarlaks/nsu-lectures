#include <stdio.h>
#include <string.h>

int issep(char ch) {
    if (ch == '.' || ch == ',' || ch == ':' || ch == ';') return 1;
    return 0;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    char in[1000001];
    scanf("%s", in);
    int l = 0;
    int a = 0;
    int f = 0;
    char s[1000001] = {0};
    fclose(stdin);
    for (int i = 0; i<10000000; i++) {
        if (in[i] == '\0' && l != 0) {
            printf("%d/%d %s\n", a, l, s);
            return 0;
        } else if (in[i] == '\0' && l == 0) {
            return 0;
        }
        if (issep(in[i]) && l != 0) {
            printf("%d/%d %s\n", a, l, s);
            a = 0;
            l = 0;
            s[0] = '\0';
        } else if (!issep(in[i])) {
            strcat(s, (char[]){in[i], '\0'});
            if ('A' <= in[i] && in[i] <= 'Z') a++;
            l++;
        }
    }
    return 0;
}