#include "primes.h"
#include <stddef.h>
#include <math.h>

#define MAX_N 10000000

static char is_prime[MAX_N + 1];
static int prime_count[MAX_N + 1];
static int initialized = 0;

static void init(void) {
    if (initialized) return;
    initialized = 1;

    for (int i = 2; i <= MAX_N; i++) {
        is_prime[i] = 1;
    }

    for (int i = 2; i * i <= MAX_N; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= MAX_N; j += i) {
                is_prime[j] = 0;
            }
        }
    }

    prime_count[0] = 0;
    for (int i = 1; i <= MAX_N; i++) {
        prime_count[i] = prime_count[i - 1] + (is_prime[i - 1] ? 1 : 0);
    }
}

static int is_prime_big(int x) {
    if (x < 2) return 0;
    if (x <= MAX_N) return is_prime[x];
    for (int d = 2; d * d <= x; d++) {
        if (x % d == 0) return 0;
    }
    return 1;
}

int isPrime(int x) {
    init();
    return is_prime_big(x);
}

int findNextPrime(int x) {
    init();
    if (x < 2) return 2;
    while (!is_prime_big(x)) {
        x++;
    }
    return x;
}

int getPrimesCount(int l, int r) {
    init();
    if (l < 0) l = 0;
    if (r > MAX_N + 1) r = MAX_N + 1;
    if (l >= r) return 0;
    return prime_count[r] - prime_count[l];
}