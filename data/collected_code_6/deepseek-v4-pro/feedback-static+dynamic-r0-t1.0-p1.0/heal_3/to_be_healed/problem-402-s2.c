#include <stdio.h>
#include <stdlib.h>

long long mul_mod(long long a, long long b, long long mod) {
    long long result = 0;
    a %= mod;
    b %= mod;
    while (b > 0) {
        if (b & 1) {
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 2610173092052214720 + 7507913613094010880 cannot be represented in type 'long long' (AFL crash: id:000004,sig:06,src:000003,time:13743,execs:8842,op:havoc,rep:2)
             * UBSan: signed integer overflow: 8142508126285856768 + 1152921504606846976 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000003,time:2772,execs:1786,op:havoc,rep:2)
             */
            result = (result + a);
            if (result >= mod) result -= mod;
        }
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 5674535530486824960 + 5674535530486824960 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000003,time:2772,execs:1786,op:havoc,rep:2)
         * UBSan: signed integer overflow: 7507913613094010880 + 7507913613094010880 cannot be represented in type 'long long' (AFL crash: id:000004,sig:06,src:000003,time:13743,execs:8842,op:havoc,rep:2)
         */
        a = (a + a);
        if (a >= mod) a -= mod;
        b >>= 1;
    }
    return result;
}

long long mod_pow(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1)
            result = mul_mod(result, base, mod);
        base = mul_mod(base, base, mod);
        exp >>= 1;
    }
    return result;
}

long long mod_inverse(long long a, long long p) {
    return mod_pow(a, p - 2, p);
}
 /* Possible weaknesses found:
  *  test case 2 failed: expected 10, got 0
  */

long long ncr_mod_p(long long n, long long r, long long p) {
    if (r < 0 || r > n)
        return 0;
    if (p <= 1)
        return 0;

    if (r > n - r)
        r = n - r;

    long long numerator = 1;
    long long denominator = 1;

    for (long long i = n - r + 1; i <= n; ++i)
        numerator = mul_mod(numerator, i % p, p);

    for (long long i = 1; i <= r; ++i)
        denominator = mul_mod(denominator, i % p, p);

    return mul_mod(numerator, mod_inverse(denominator, p), p);
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000003,time:1279,execs:834,op:havoc,rep:2; likely memory-safety defect
  */

int main(void) {
    long long n, r, p;
    if (scanf("%lld %lld %lld", &n, &r, &p) != 3)
        return 1;

    printf("%lld\n", ncr_mod_p(n, r, p));
    return 0;
}