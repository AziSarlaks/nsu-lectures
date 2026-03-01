#include <stdio.h>
#include <math.h>

typedef long long ll;

int solve_negative_pell(ll p, ll *X, ll *Y) {
    ll a0 = (ll)sqrt(p);
    if (a0 * a0 == p) return 0;
    
    ll m = 0, d = 1, a = a0;
    ll h1 = 1, k1 = 0;
    ll h = a0, k = 1;
    
    ll m_start = m, d_start = d, a_start = a;
    
    for (int period = 1; period <= 200000; period++) {
        m = d * a - m;
        d = (p - m * m) / d;
        a = (a0 + m) / d;
        
        ll next_h = a * h + h1;
        ll next_k = a * k + k1;
        
        h1 = h; k1 = k;
        h = next_h; k = next_k;
        
        if (period % 2 == 1) {
            __int128 lhs = (__int128)h1 * h1 - (__int128)p * k1 * k1;
            if (lhs == -1 && h1 <= 1000000000000000LL) {
                *X = h1;
                *Y = k1;
                return 1;
            }
        }
        
        if (m == m_start && d == d_start && a == a_start) {
            break;
        }
    }
    
    return 0;
}

int main() {
    int T;
    scanf("%d", &T);
    
    while (T--) {
        ll p;
        scanf("%lld", &p);
        
        ll x, y;
        if (solve_negative_pell(p, &x, &y)) {
            printf("%lld %lld\n", x, y);
        } else {
            printf("no solutions\n");
        }
    }
    
    return 0;
}