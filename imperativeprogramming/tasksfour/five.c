#include <stdio.h>
#include <string.h>

char *split(char *Str, char *separators) {
    static char res[1000001] = {0};
    static char res2[1000001] = {0};
    int len = 0;
    int alpha = 0;
    while (*Str) {
        if (!strchr(separators, *Str)) {
            char temp[2] = {*Str, '\0'};
            strcat(res, temp);
            len++;
            if ('A' <= *Str && *Str <= 'Z') {
                alpha++;
            }
            Str++;
        } else if (strchr(separators, *Str) && len == 0) {
            Str++;
        } else if (strchr(separators, *Str)){
            char l = len + '0';
            char a = alpha + '0';
            char temp[4] = {a, '/', l, '\0'};
            strcat(res2, temp);
            strcat(res2, res);
            res[0] = '\0';
            len = 0;
            alpha = 0;
            Str++;
        }
        if (len > 0 && *Str == '\0') {
            char l = len + '0';
            char a = alpha + '0';
            strcat(res2, (char[]){a, '/', l, '\0'});
            strcat(res2, res);
        }
    }
    return res2;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    char sep[] = {'.', ',', ':', ';', '\0'};
    char in[1000001];
    scanf("%s", in);
    fclose(stdin);
    char *res = split(in, sep);
    if (res[0] != '\0') {

        printf("%c%c%c ", res[0], res[1], res[2]);
        int f = 1;
        for (int i = 3; i < 10000000; i++) {
            if ('0' <= res[i] && res[i] <= '9' && f == 1) {
                f = 0;
                printf("\n");
                printf("%c", res[i]);
            } else if (f == 0 && '/' == res[i]) {
                printf("%c", res[i]);
                f = 2;
            } else if ('0' <= res[i] && res[i] <= '9' && f == 2) {
                printf("%c", res[i]);
                printf(" ");
                f = 1;
            } else if (res[i] == '\0') {
                break;
            } else {
                printf("%c", res[i]);
            }
        }
        fclose(stdout);
    }
    return 0;
}