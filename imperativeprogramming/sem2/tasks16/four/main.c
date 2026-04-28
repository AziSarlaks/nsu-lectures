typedef struct Factors {
    int k;
    int primes[32];
    int powers[32];
} Factors;

void Factorize(int X, Factors *res);

int scanf(const char *fmt, ...);
int printf(const char *fmt, ...);

int main() {
    int M;
    scanf("%d", &M); 

    for (int i = 0; i < M; i++) {
        int X;
        scanf("%d", &X);
        Factors f;
        Factorize(X, &f);

        printf("%d =", X);
        if (f.k == 0) {
            printf(" 1\n");
        } else {
            for (int j = 0; j < f.k; j++) {
                if (j > 0) printf(" *");
                printf(" %d^%d", f.primes[j], f.powers[j]);
            }
            printf("\n");
        }
    }

    return 0;
}