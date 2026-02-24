#include <stdio.h>
#include <math.h>

#define MAX 105

int main()
{
    int n;
    scanf("%d", &n);
    
    long double x[MAX], y[MAX];
    long double a[MAX][MAX + 1];
    
    for (int i = 0; i < n; i++) {
        scanf("%Lf%Lf", &x[i], &y[i]);
    }
    
    for (int i = 0; i < n; i++) {
        long double pow = 1.0;
        for (int j = 0; j < n; j++) {
            a[i][j] = pow;
            pow *= x[i];
        }
        a[i][n] = y[i];
    }
    
    for (int i = 0; i < n; i++) {
        int max_row = i;
        long double max_val = fabsl(a[i][i]);
        
        for (int j = i + 1; j < n; j++) {
            if (fabsl(a[j][i]) > max_val) {
                max_val = fabsl(a[j][i]);
                max_row = j;
            }
        }
        
        if (max_row != i) {
            for (int j = 0; j <= n; j++) {
                long double temp = a[i][j];
                a[i][j] = a[max_row][j];
                a[max_row][j] = temp;
            }
        }
        
        for (int j = i + 1; j < n; j++) {
            long double factor = a[j][i] / a[i][i];
            for (int k = i + 1; k <= n; k++) {
                a[j][k] -= factor * a[i][k];
            }
            a[j][i] = 0;
        }
    }
    
    long double c[MAX];
    for (int i = n - 1; i >= 0; i--) {
        c[i] = a[i][n];
        for (int j = i + 1; j < n; j++) {
            c[i] -= a[i][j] * c[j];
        }
        c[i] /= a[i][i];
    }
    
    for (int i = 0; i < n; i++) {
        printf("%.10Lf ", c[i]);
    }
    
    return 0;
}