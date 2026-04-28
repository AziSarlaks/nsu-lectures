typedef struct Factors {
    int k;
    int primes[32];
    int powers[32];
} Factors;

void Factorize(int X, Factors *res) {
    res->k = 0;
    if (X == 1) return;

    int n = X;
    int p = 2;
    
    while (p * p <= n) {
        if (n % p == 0) {
            int cnt = 0;
            while (n % p == 0) {
                n /= p;
                cnt++;
            }
            res->primes[res->k] = p;
            res->powers[res->k] = cnt;
            res->k++;
        }
        p++;
    }
    
    if (n > 1) {
        res->primes[res->k] = n;
        res->powers[res->k] = 1;
        res->k++;
    }
}