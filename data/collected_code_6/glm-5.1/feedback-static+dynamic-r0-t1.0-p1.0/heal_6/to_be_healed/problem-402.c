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
        if (b % 2 == 1) {
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 3294464004646478649 + 8539818392200282112 cannot be represented in type 'll' (aka 'long long') (AFL crash: id:000000,sig:06,src:000000,time:2183,execs:949,op:havoc,rep:8)
             */
            result = (result + a) % mod;
        }
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 4611686018427387904 * 2 cannot be represented in type 'll' (aka 'long long') (AFL crash: id:000000,sig:06,src:000000,time:2183,execs:949,op:havoc,rep:8)
         */
        a = (a * 2) % mod;
        b = b / 2;
    }
    return result;
}

ll mod_exp(ll base, ll exp, ll mod) {
    ll result = 1;
    base = base % mod;
    if (base < 0) base += mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = mod_mul(result, base, mod);
        }
        exp = exp / 2;
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
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000001,sig:06,src:000017,time:37400,execs:15865,op:havoc,rep:3; likely memory-safety defect
  */

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