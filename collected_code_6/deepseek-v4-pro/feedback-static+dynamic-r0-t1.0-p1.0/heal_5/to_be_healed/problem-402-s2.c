#include <stdio.h>
#include <stdlib.h>

long long mul_mod(long long a, long long b, long long mod) {
    long long result = 0;
    a %= mod;
    b %= mod;
    while (b > 0) {
        if (b & 1) {
            result = (result >= mod - a) ? (result - mod + a) : (result + a);
        }
        a = (a >= mod - a) ? (a - mod + a) : (a + a);
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
    long long r0 = a, r1 = p;
    long long s0 = 1, s1 = 0;
    while (r1 > 0) {
        long long q = r0 / r1;
        long long tmp = r0 - q * r1;
        r0 = r1;
        r1 = tmp;
        tmp = s0 - q * s1;
        s0 = s1;
        s1 = tmp;
    }
    if (r0 != 1) return 0;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 1 + 9223372036854775807 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000027,time:23239,execs:15521,op:havoc,rep:3)
     */
    return (s0 % p + p) % p;
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

    if (n >= p) {
        long long res = 1;
        while (n > 0 || r > 0) {
            long long ni = n % p;
            long long ri = r % p;
            if (ri > ni) return 0;
            res = mul_mod(res, ncr_mod_p(ni, ri, p), p);
            n /= p;
            r /= p;
        }
        return res;
    }

    long long numerator = 1;
    long long denominator = 1;

    for (long long i = n - r + 1; i <= n; ++i)
        numerator = mul_mod(numerator, i % p, p);

    for (long long i = 1; i <= r; ++i)
        denominator = mul_mod(denominator, i % p, p);

    return mul_mod(numerator, mod_inverse(denominator, p), p);
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000001,sig:06,src:000003,time:23761,execs:15876,op:havoc,rep:8; likely memory-safety defect
  */

int main(void) {
    long long n, r, p;
    if (scanf("%lld %lld %lld", &n, &r, &p) != 3)
        return 1;

    printf("%lld\n", ncr_mod_p(n, r, p));
    return 0;
}