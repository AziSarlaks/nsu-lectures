#include <stdio.h>

#define MOD 1000000007
#define MAX_N 1000000

long long F[MAX_N + 1];
long long iF[MAX_N + 1];

long long mp(long long a, long long b, long long m)
{
    long long res = 1;
    while (b > 0)
    {
        if (b & 1)
        {
            res = (res * a) % m;
        }
        a = (a * a) % m;
        b >>= 1;
    }
    return res;
}

void precompute() {
    F[0] = 1;
    for (int i = 1; i <= MAX_N; i++) {
        F[i] = (F[i-1] * i) % MOD;
    }
    
    iF[MAX_N] = mp(F[MAX_N], MOD-2, MOD);
    for (int i = MAX_N; i >= 1; i--) {
        iF[i-1] = (iF[i] * i) % MOD;
    }
}

long long C(int n, int k) {
    if (k < 0 || k > n) return 0;
    return F[n] * iF[k] % MOD * iF[n-k] % MOD;
}

int main() {
    precompute();
    
    int T;
    scanf("%d", &T);
    
    while (T--) {
        int N, K;
        scanf("%d %d", &N, &K);
        printf("%lld\n", C(N, K));
    }
    
    return 0;
}