#include <stdio.h>

double custom_exp(double x) {
    if (x < 0) {
        return 1.0 / custom_exp(-x);
    }
    
    double result = 1.0;
    double term = 1.0;
    int n = 1;
    
    while (1) {
        term = term * x / n;
        if (term < 1e-15) {
            break;
        }
        result += term;
        n++;
        
        if (n > 1000) {
            break;
        }
    }
    
    return result;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    int c;
    scanf("%d", &c);
    
    for (int i = 0; i < c; i++) {
        double x;
        scanf("%lf", &x);
        
        double exp_x = custom_exp(x);
        printf("%.15g\n", exp_x);
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}