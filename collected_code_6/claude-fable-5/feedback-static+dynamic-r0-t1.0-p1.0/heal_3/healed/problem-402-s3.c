#include <stdio.h>
#include <stdlib.h>

long long mul_mod(long long a, long long b, long long mod);
long long power_mod(long long base, long long exp, long long mod);
long long mod_inverse(long long a, long long p);
long long ncr_small_mod_p(long long n, long long r, long long p);
long long ncr_mod_p(long long n, long long r, long long p);

long long mul_mod(long long a, long long b, long long mod)
{
    __int128 res;

    if (mod <= 0) {
        return -1;
    }

    a %= mod;
    if (a < 0) {
        a += mod;
    }

    b %= mod;
    if (b < 0) {
        b += mod;
    }

    res = (__int128)a * (__int128)b;
    return (long long)(res % mod);
}

long long power_mod(long long base, long long exp, long long mod)
{
    long long result = 1;

    if (mod <= 0) {
        return -1;
    }

    base = base % mod;
    if (base < 0) {
        base += mod;
    }

    while (exp > 0) {
        if (exp & 1LL) {
            result = mul_mod(result, base, mod);
        }
        base = mul_mod(base, base, mod);
        exp >>= 1LL;
    }

    return result;
}

long long mod_inverse(long long a, long long p)
{
    if (p <= 1) {
        return -1;
    }

    a %= p;
    if (a < 0) {
        a += p;
    }

    if (a == 0) {
        return -1;
    }

    return power_mod(a, p - 2, p);
}

long long ncr_small_mod_p(long long n, long long r, long long p)
{
    long long numerator = 1;
    long long denominator = 1;
    long long p_exponent = 0;
    long long i;
    long long inv;

    if (n < 0 || r < 0 || p <= 1) {
        return -1;
    }

    if (r > n) {
        return 0;
    }

    if (r > n - r) {
        r = n - r;
    }

    for (i = 0; i < r; i++) {
        long long num = n - i;
        long long den = i + 1;

        while (num % p == 0) {
            num /= p;
            p_exponent++;
        }

        while (den % p == 0) {
            den /= p;
            p_exponent--;
        }

        numerator = mul_mod(numerator, num, p);
        denominator = mul_mod(denominator, den, p);
    }

    if (p_exponent > 0) {
        return 0;
    }

    inv = mod_inverse(denominator, p);
    if (inv < 0) {
        return -1;
    }

    return mul_mod(numerator, inv, p);
}

long long ncr_mod_p(long long n, long long r, long long p)
{
    long long result = 1;

    if (p <= 1 || n < 0 || r < 0) {
        return -1;
    }

    if (r > n) {
        return 0;
    }

    while (n > 0 || r > 0) {
        long long ni = n % p;
        long long ri = r % p;
        long long partial;

        if (ri > ni) {
            return 0;
        }

        partial = ncr_small_mod_p(ni, ri, p);
        if (partial < 0) {
            return -1;
        }

        result = mul_mod(result, partial, p);
        if (result < 0) {
            return -1;
        }

        n /= p;
        r /= p;
    }

    return result;
}

int main(void)
{
    long long n;
    long long r;
    long long p;
    long long result;

    printf("Enter n, r, and prime p: ");
    if (scanf("%lld %lld %lld", &n, &r, &p) != 3) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (n < 0 || r < 0 || p <= 1) {
        fprintf(stderr, "Invalid values: n and r must be non-negative, p must be a prime greater than 1\n");
        return EXIT_FAILURE;
    }

    result = ncr_mod_p(n, r, p);
    if (result < 0) {
        fprintf(stderr, "Computation failed\n");
        return EXIT_FAILURE;
    }

    printf("nCr %% p = %lld\n", result);

    return EXIT_SUCCESS;
}