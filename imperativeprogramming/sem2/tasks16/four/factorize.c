#include <math.h>

typedef struct Factors {
    int k;
    int primes[32];
    int powers[32];
} Factors;

void Factorize(int X, Factors *res) {
    res->k = 0;
    if (X == 1) return;

    int n = X;
    for (int p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            int count = 0;
            while (n % p == 0) {
                n /= p;
                count++;
            }
            res->primes[res->k] = p;
            res->powers[res->k] = count;
            res->k++;
        }
    }
    if (n > 1) {
        res->primes[res->k] = n;
        res->powers[res->k] = 1;
        res->k++;
    }
}