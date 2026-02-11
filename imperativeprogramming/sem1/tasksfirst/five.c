#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    freopen("input.txt", "r", stdin);
    int a, b;
    float res1, res2, res3;
    int res4;
    scanf("%d %d", &a, &b);
    float fa = a, fb = b;

    res1 = floor(fa/fb);
    res2 = ceil(fa/fb);
    res3 = a/b;
    if (a >= 0) {
        res4 = a%b;
    } else {
        res4 = a - b*(floor(fa/fb));
    }
    // if (res1 == -0) res1 = 0;
    // if (res2 == -0) res2 = 0;
    // if (res3 == -0) res3 = 0;
    // if (res4 == -0) res4 = 0;

    fclose(stdin);
    
    freopen("output.txt", "w", stdout);
    printf("%.f %.f %.f %d", res1, res2, res3, res4);
    fclose(stdout);
    return 0;
}