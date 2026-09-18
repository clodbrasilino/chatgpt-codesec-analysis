#include <stdio.h>
#include <stdlib.h>

typedef long long ll;
typedef unsigned long long ull;

ull mod_mul(ll a, ll b, ll mod) {
    ll result = 0;
    a = a % mod;
    if (a < 0) a += mod;
    b = b % mod;
    if (b < 0) b += mod;
    while (b > 0) {
        if (b & 1) {
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 1098154668215492883 + 8995520821969944576 cannot be represented in type 'll' (aka 'long long') (AFL crash: id:000000,sig:06,src:000003,time:1293,execs:662,op:havoc,rep:1)
             */
            result = result + a;
            if (result >= mod) result -= mod;
        }
        /* Possible weaknesses found:
         * UBSan: left shift of 4611686018427387904 by 1 places cannot be represented in type 'll' (aka 'long long') (AFL crash: id:000000,sig:06,src:000003,time:1293,execs:662,op:havoc,rep:1)
         */
        a = a << 1;
        if (a >= mod) a -= mod;
        b = b >> 1;
    }
    return result;
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
        return mod_mul(ncr_mod_p(n / p, r / p, p), ncr_mod_p(n % p, r % p, p), p);
    }
    r = r < (n - r) ? r : (n - r);
    ll res = 1;
    for (ll i = 1; i <= r; i++) {
        res = mod_mul(res, (n - r + i) % p, p);
        res = mod_mul(res, mod_exp(i, p - 2, p), p);
    }
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