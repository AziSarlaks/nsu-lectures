#include <stdio.h>
#include <stdlib.h>

int main() {
    char tnum1[3], tnum2[3];
    int num1, num2, divis;
    float avg;

    scanf("%s %s", tnum1, tnum2);
    num1 = atoi(tnum1);
    num2 = atoi(tnum2);
    if (num2 != 0) {
        divis = num1 / num2;
        avg = (num1 + num2) / 2.00;

        printf("%d\n", divis);
        printf("%.2f\n", avg);
    }
    return 0;
}