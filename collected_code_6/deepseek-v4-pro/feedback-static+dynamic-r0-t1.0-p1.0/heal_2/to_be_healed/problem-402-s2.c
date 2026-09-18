#include <stdio.h>
#include <stdlib.h>

long long mul_mod(long long a, long long b, long long mod) {
    long long result = 0;
    a %= mod;
    b %= mod;
    while (b > 0) {
        if (b & 1)
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 8142508126285856768 + 1152921504606846976 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000003,time:11034,execs:2052,op:havoc,rep:1)
             * UBSan: signed integer overflow: 4388233221854697600 + 5850977629139596800 cannot be represented in type 'long long' (AFL crash: id:000004,sig:06,src:000015,time:56946,execs:21126,op:havoc,rep:1)
             */
            result = (result + a) % mod;
        /* Possible weaknesses found:
         * UBSan: left shift of 5674535530486824960 by 1 places cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000003,time:11034,execs:2052,op:havoc,rep:1)
         * UBSan: left shift of 5850977629139596800 by 1 places cannot be represented in type 'long long' (AFL crash: id:000004,sig:06,src:000015,time:56946,execs:21126,op:havoc,rep:1)
         */
        a = (a << 1) % mod;
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

    r = (r > n - r) ? n - r : r;

    long long numerator = 1;
    for (long long i = n - r + 1; i <= n; ++i)
        numerator = mul_mod(numerator, i % p, p);

    long long denominator = 1;
    for (long long i = 1; i <= r; ++i)
        denominator = mul_mod(denominator, i % p, p);

    return mul_mod(numerator, mod_inverse(denominator, p), p);
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000003,time:987,execs:526,op:havoc,rep:3; likely memory-safety defect
  */

int main(void) {
    long long n, r, p;
    if (scanf("%lld %lld %lld", &n, &r, &p) != 3)
        return 1;

    printf("%lld\n", ncr_mod_p(n, r, p));
    return 0;
}