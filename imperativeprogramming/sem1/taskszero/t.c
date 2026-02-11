#include <stdio.h>
#include <stdlib.h>

int main() {
    char tnum1[3], tnum2[3];
    int num1, num2, mult, rem1, rem2;

    scanf("%s %s", tnum1, tnum2);
    num1 = atoi(tnum1);
    num2 = atoi(tnum2);
    if ((num1 != 0) && (num2 != 0)) {
        mult = num1 * num2;
        rem1 = num1 % num2;
        rem2 = num2 % num1;

        printf("%d\n", mult);
        printf("%d %d\n", rem1, rem2);
    }
    return 0;
}

