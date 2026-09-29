#include <stdio.h>
#include <stdlib.h>

typedef long long ll;
typedef unsigned long long ull;

ull mod_mul(ll a, ll b, ll mod) {
    ll la = a % mod;
    if (la < 0) la += mod;
    ll lb = b % mod;
    if (lb < 0) lb += mod;
    ull ua = la;
    ull ub = lb;
    ull ures = 0;
    ull umod = mod;
    while (ub > 0) {
        if (ub & 1) {
            ures = ures + ua;
            if (ures >= umod) ures -= umod;
        }
        ua = ua << 1;
        if (ua >= umod) ua -= umod;
        ub = ub >> 1;
    }
    return ures;
}

ll mod_exp(ll base, ll exp, ll mod) {
    ll result = 1;
    base = base % mod;
    if (base < 0) base += mod;
    while (exp > 0) {
        if (exp & 1) {
            result = mod_mul(result, base, mod);
        }
        exp = exp >> 1;
        base = mod_mul(base, base, mod);
    }
    return result;
}
 /* Possible weaknesses found:
  *  test case 2 failed: expected 10, got 0
  */

ll ncr_mod_p(ll n, ll r, ll p) {
    if (r < 0 || r > n) {
        return 0;
    }
    if (r == 0 || r == n) {
        return 1;
    }
    if (p == 1) {
        return 0;
    }
    if (n >= p) {
        if ((n % p) < (r % p)) {
            return 0;
        }
        return mod_mul(ncr_mod_p(n / p, r / p, p), ncr_mod_p(n % p, r % p, p), p);
    }
    r = r < (n - r) ? r : (n - r);
    ll res = 1;
    ll den = 1;
    for (ll i = 1; i <= r; i++) {
        res = mod_mul(res, (n - r + i), p);
        den = mod_mul(den, i, p);
    }
    res = mod_mul(res, mod_exp(den, p - 2, p), p);
    return res;
}

int main(void) {
    ll n, r, p;
    while (scanf("%lld %lld %lld", &n, &r, &p) == 3) {
        if (p <= 0) {
            printf("0\n");
        } else {
            printf("%lld\n", ncr_mod_p(n, r, p));
        }
    }
    return 0;
}