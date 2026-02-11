#include <stdio.h>

int calcLetters(char *iStr, int *oLowerCnt, int *oUpperCnt, int *oDigitsCnt) {
    int len = 0;
    while (*iStr) {
        if (48 <= (int)*iStr && (int)*iStr <= 57) {
            (*oDigitsCnt)++;
        } else if (65 <= (int)*iStr && (int)*iStr <= 90) {
            (*oUpperCnt)++;
        } else if (97 <= (int)*iStr && (int)*iStr <= 122) {
            (*oLowerCnt)++;
        }
        if ((int)*iStr != 10) {
            len++;
        } else {
            return len;
        }
        iStr++;
    }
    return len;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int lc = 0;
    int uc = 0;
    int od = 0;
    int len = 0;
    int lenc = 0;
    while (1) {
        char str[10000];
        lenc++;
        lc = 0;
        uc = 0;
        od = 0;
        if (fgets(str, 1000, stdin) == NULL) {
            break;
        }
        len = calcLetters(str, &lc, &uc, &od);
        printf("Line %d has %d chars: %d are letters (%d lower, %d upper), %d are digits.\n", lenc, len, lc+uc, lc, uc, od);
    }
}