#include <stdio.h>

typedef long long ll;
typedef __int128 lll;

ll egcd(ll a, ll b, ll *x, ll *y) {
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }
    ll x1, y1;
    ll g = egcd(b, a % b, &x1, &y1);
    *x = y1;
    *y = x1 - y1 * (a / b);
    return g;
}

ll mi(ll a, ll mod) {
    ll x, y;
    egcd(a, mod, &x, &y);
    x %= mod;
    if (x < 0) x += mod;
    return x;
}

int main() {
    int k;
    scanf("%d", &k);

    ll M[2000], A[2000];

    for (int i = 0; i < k; i++)
        scanf("%lld", &M[i]);

    for (int i = 0; i < k; i++)
        scanf("%lld", &A[i]);

    ll total = 1;
    for (int i = 0; i < k; i++)
        total *= M[i];

    lll X = 0;

    for (int i = 0; i < k; i++) {
        ll Ni = total / M[i];
        ll inv = mi(Ni % M[i], M[i]);
        X = (X + (lll)A[i] * Ni % total * inv % total) % total;
    }

    printf("%lld\n", (ll)X);

    return 0;
}