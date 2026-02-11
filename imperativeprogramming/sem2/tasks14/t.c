#include <stdio.h>
#include <stdlib.h>

long long egcd(long long a, long long b, long long *x, long long *y) {
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }
    long long x1, y1;
    long long gcd = egcd(b, a % b, &x1, &y1);
    *x = y1;
    *y = x1 - (a / b) * y1;
    return gcd;
}

long long mi(long long a, long long m) {
    long long x, y;
    long long gcd = egcd(a, m, &x, &y);
    return (x % m + m) % m;
}

int main() {
    int k;
    scanf("%d", &k);
    
    long long *M = malloc(k * sizeof(long long));
    long long *A = malloc(k * sizeof(long long));
    
    for (int i = 0; i < k; i++) {
        scanf("%lld", &M[i]);
    }
    for (int i = 0; i < k; i++) {
        scanf("%lld", &A[i]);
    }
    
    long long M_all = 1;
    for (int i = 0; i < k; i++) {
        M_all *= M[i];
    }
    
    long long X = 0;
    for (int i = 0; i < k; i++) {
        long long Mi_prime = M_all / M[i];
        long long inv = mi(Mi_prime, M[i]);
        X += A[i] * Mi_prime % M_all * inv % M_all;
        X %= M_all;
    }
    
    printf("%lld\n", X);
    
    free(M);
    free(A);
    return 0;
}