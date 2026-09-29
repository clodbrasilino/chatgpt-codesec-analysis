#include <stdio.h>
#include <stdlib.h>

long long mul_mod(long long a, long long b, long long p) {
    long long res = 0;
    a %= p;
    b %= p;
    if (a < 0) a += p;
    if (b < 0) b += p;
    while (b > 0) {
        if (b & 1)
            res = (res + a) % p;
        a = (a + a) % p;
        b >>= 1;
    }
    return res;
}

long long power(long long a, long long b, long long p) {
    long long res = 1;
    a %= p;
    if (a < 0) a += p;
    while (b > 0) {
        if (b & 1)
            res = mul_mod(res, a, p);
        b >>= 1;
        a = mul_mod(a, a, p);
    }
    return res;
}

long long mod_inverse(long long n, long long p) {
    return power(n, p - 2, p);
}

long long ncr_mod_p(long long n, long long r, long long p) {
    if (r < 0 || r > n)
        return 0;
    if (r == 0 || r == n)
        return 1;
    if (r > n - r)
        r = n - r;

    long long numerator = 1;
    long long denominator = 1;

    for (long long i = 0; i < r; i++) {
        numerator = mul_mod(numerator, (n - i) % p, p);
        denominator = mul_mod(denominator, (i + 1) % p, p);
    }

    return mul_mod(numerator, mod_inverse(denominator, p), p);
}

int main(void) {
    long long n, r, p;
    if (scanf("%lld %lld %lld", &n, &r, &p) != 3) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    if (p <= 1) {
        fprintf(stderr, "p must be a prime number greater than 1\n");
        return EXIT_FAILURE;
    }
    printf("%lld\n", ncr_mod_p(n, r, p));
    return EXIT_SUCCESS;
}