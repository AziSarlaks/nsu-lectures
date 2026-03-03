#include <stdio.h>
#include <math.h>

double Function(double x);

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int M;
    scanf("%d", &M);

    double h = 1e-8;    

    for (int i = 0; i < M; i++) {
        double x;
        scanf("%lf", &x);

        double deriv;
        if (x < h) {
            deriv = (Function(x + h) - Function(x)) / h;
        } else if (x > 1.0 - h) {
            deriv = (Function(x) - Function(x - h)) / h;
        } else {
            deriv = (Function(x + h) - Function(x - h)) / (2.0 * h);
        }

        printf("%.15lf\n", deriv);
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}