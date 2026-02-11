#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n;
    scanf("%d", &n);
    float negc = 0, zeroc = 0, pozc = 0;
    double neg, zero, poz;
    for (int i = 0; i<n; i++) {
        int l;
        scanf("%d", &l);
        if (l < 0) {
            negc += 1;
        } else if (l == 0) {
            zeroc += 1;
        } else if (l > 0) {
            pozc += 1;
        }
    }
    fclose(stdin);
    neg = negc/n;
    zero = zeroc/n;
    poz = pozc/n;
    // poz *= 100000;
    // zero *= 100000;
    // neg *= 100000;
    // int res1 = (int)neg;
    // int res2 = (int)zero;
    // int res3 = (int)poz;
    // neg = res1 / 100000.0;
    // zero = res2 / 100000.0;
    // poz = res3 / 100000.0;
    printf("%0.5lf %0.5lf %0.5lf", neg, zero, poz);
    fclose(stdout);
    return 0;
}