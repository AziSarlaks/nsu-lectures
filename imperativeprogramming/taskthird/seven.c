#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int p, q;
    char n[50];
    int decimal = 0;

    scanf("%d %d %s", &p, &q, n);
    for (int i = 0; i < strlen(n); i++) {
        if ((int)n[i] < 58) {
            decimal += (n[i]-'0') * pow(p, strlen(n) - 1 - i);
        } else {
            decimal += (n[i]-'W') * pow(p, strlen(n) - 1 - i);
        }
    }
    int ti = 0;
    int result[100];
    int co = 0;
    while (decimal > 0) {
        result[ti] = decimal % q;
        ti += 1;
        decimal /= q;
    }
    for (int i = ti-1; i>=0; i--) {
        if (result[i] > 9) {
            printf("%c", result[i] + 'W');
        }
        else {
            printf("%d", result[i]);
        }
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}