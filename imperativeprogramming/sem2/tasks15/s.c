#include <stdio.h>
#include <math.h>

#define MAXN 205
#define EPS 1e-12

int main() {
    int n;
    scanf("%d", &n);

    double a[MAXN][MAXN];

    for (int i = 0; i < n; i++)
        for (int j = 0; j <= n; j++)
            scanf("%lf", &a[i][j]);

    for (int i = 0; i < n; i++) {
        int maxRow = i;
        for (int k = i + 1; k < n; k++)
            if (fabs(a[k][i]) > fabs(a[maxRow][i]))
                maxRow = k;

        for (int j = 0; j <= n; j++) {
            double tmp = a[i][j];
            a[i][j] = a[maxRow][j];
            a[maxRow][j] = tmp;
        }

        double pivot = a[i][i];
        for (int j = i; j <= n; j++)
            a[i][j] /= pivot;

        for (int k = i + 1; k < n; k++) {
            double factor = a[k][i];
            for (int j = i; j <= n; j++)
                a[k][j] -= factor * a[i][j];
        }
    }

    double x[MAXN];

    for (int i = n - 1; i >= 0; i--) {
        x[i] = a[i][n];
        for (int j = i + 1; j < n; j++)
            x[i] -= a[i][j] * x[j];
    }

    for (int i = 0; i < n; i++)
        printf("%.10f\n", x[i]);

    return 0;
}