#include <stdio.h>
#include <stdlib.h>

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    char curr;
    short f = 0;
    // f = 0 - base state (no comment)
    // f = 1 - after first '/'
    // f = 2 - one line comment
    // f = 3 - multi line comment
    // f = 4 - after '*' end of multi line comment
    while (1) {
        if (scanf("%c", &curr) != 1) {
            if (f == 1) {
                printf("%c", '/');
            }
            break;
        } 
        if (f == 1 && curr != '*' && curr != '/') {
            printf("%c%c", '/', curr);
            f = 0;
        } else {
            if (curr == '/' && f == 0) {
                f = 1;
            } else if (curr == '/' && f == 1) {
                f = 2;
            } else if (curr == '*' && f == 1) {
                f = 3;
            } else if (curr == '\n' && f == 2) {
                f = 0;
                printf("\n");
            } else if (curr == '\n' && f == 3) {
                printf("\n");
            } else if (curr == '*' && (f == 3 || f == 4)) {
                f = 4;
            } else if (curr == '/' && f == 4) {
                f = 0;
            } else if (f == 4 && curr != '/' && curr != '*') {
                f = 3;
            } else if (f == 0) {
                printf("%c", curr);
            }
        }
    }
    return 0;
}
