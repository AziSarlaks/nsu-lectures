#include <stdio.h>

double s(double x) {
    double pi = 3.14;
    double twice_pi = 3.14*2;

    x = x - (int)(x / twice_pi) * twice_pi;
    if (x > pi) x -= twice_pi;
    if (x < -pi) x += twice_pi;
    double res = 0.0;
    double x_pow = x;
    double fact = 1.0;
    int sign = 1;
    double term;

    for (int i = 0; i<20; i++) {
        term = sign * x_pow / fact;
        res += term;
        sign = -sign;
        x_pow *= x * x;
        fact *= (2*i + 2) * (2*i + 3);
        
        if (term < 1e-15 && term > -1e-15) {
            break;
        }
    }
    return res;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    int c;
    scanf("%d", &c);

    for (int i = 0; i < c; i++) {
        double x;
        scanf("%lf", &x);
        
        double sin_x = s(x);
        printf("%0.15lf\n", sin_x);
    }


    fclose(stdin);
    fclose(stdout);
    return 0;
}