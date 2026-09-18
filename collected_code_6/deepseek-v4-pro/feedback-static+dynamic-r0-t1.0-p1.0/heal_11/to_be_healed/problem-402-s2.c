#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long mul_mod(long long a, long long b, long long mod) {
    long long result = 0;
    a %= mod;
    b %= mod;
    while (b > 0) {
        if (b & 1) {
            if (result >= mod - a)
                result = result - mod + a;
            else
                result = result + a;
        }
        if (a >= mod - a)
            a = a - mod + a;
        else
            a = a + a;
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
    long long t0 = 0, t1 = 1;
    while (r1 > 0) {
        long long q = r0 / r1;
        long long tmp = r0 - q * r1;
        r0 = r1;
        r1 = tmp;
        tmp = s0 - q * s1;
        s0 = s1;
        s1 = tmp;
        tmp = t0 - q * t1;
        t0 = t1;
        t1 = tmp;
    }
    if (r0 != 1) return -1;
    long long res = s0 % p;
    if (res < 0) res += p;
    return res;
}

long long ncr_mod_p_small(long long n, long long r, long long p) {
    if (r < 0 || r > n) return 0;
    if (r > n - r) r = n - r;

    long long numerator = 1;
    long long denominator = 1;

    for (long long i = n - r + 1; i <= n; ++i)
        numerator = mul_mod(numerator, i % p, p);

    for (long long i = 1; i <= r; ++i)
        denominator = mul_mod(denominator, i % p, p);

    long long inv_den = mod_inverse(denominator, p);
    if (inv_den == -1) {
        long long num = numerator;
        long long den = denominator;
        long long g = p;
        while (den % g == 0 && num % g == 0) {
            num /= g;
            den /= g;
        }
        if (den % p == 0) return 0;
        inv_den = mod_inverse(den, p);
        if (inv_den == -1) return 0;
        return mul_mod(num, inv_den, p);
    }
    return mul_mod(numerator, inv_den, p);
}
 /* Possible weaknesses found:
  *  test case 0 failed: expected 6, got <no output>
  *  test case 1 failed: expected 25, got <no output>
  *  test case 2 failed: expected 10, got <no output>
  */

long long ncr_mod_p(long long n, long long r, long long p) {
    if (r < 0 || r > n)
        return 0;
    if (p <= 1)
        return 0;

    if (r > n - r)
        r = n - r;

    long long res = 1;

    while (n > 0 || r > 0) {
        long long ni = n % p;
        long long ri = r % p;
        if (ri > ni) return 0;
        long long term = ncr_mod_p_small(ni, ri, p);
        res = mul_mod(res, term, p);
        n /= p;
        r /= p;
    }
    return res;
}

int main(void) {
    long long n, r, p;
    if (scanf("%lld %lld %lld", &n, &r, &p) != 3) {
        printf("0\n");
        return 0;
    }

    printf("%lld\n", ncr_mod_p(n, r, p));
    return 0;
}