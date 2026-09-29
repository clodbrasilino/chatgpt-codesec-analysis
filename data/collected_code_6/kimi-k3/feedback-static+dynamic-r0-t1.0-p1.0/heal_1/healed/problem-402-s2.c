#include <stdio.h>
#include <stdlib.h>

static long long safe_multiply(long long a, long long b, long long mod) {
    if (mod <= 0) {
        return 0;
    }
    a %= mod;
    if (a < 0) {
        a += mod;
    }
    b %= mod;
    if (b < 0) {
        b += mod;
    }
    unsigned long long ua = (unsigned long long)a;
    unsigned long long ub = (unsigned long long)b;
    unsigned long long um = (unsigned long long)mod;
    unsigned long long result = 0;
    while (ub > 0) {
        if (ub & 1) {
            result += ua;
            if (result >= um) {
                result -= um;
            }
        }
        ua <<= 1;
        if (ua >= um) {
            ua -= um;
        }
        ub >>= 1;
    }
    return (long long)result;
}

long long power(long long x, long long y, long long p) {
    long long res = 1 % p;
    x = x % p;
    if (x < 0) {
        x += p;
    }
    while (y > 0) {
        if (y & 1) {
            res = safe_multiply(res, x, p);
        }
        y = y >> 1;
        x = safe_multiply(x, x, p);
    }
    return res;
}

long long modInverse(long long n, long long p) {
    return power(n, p - 2, p);
}

long long nCrModPFermat(long long n, long long r, long long p) {
    if (n < r) {
        return 0;
    }
    if (n == r) {
        return 1;
    }
    if (r > n - r) {
        r = n - r;
    }
    long long numerator = 1;
    for (long long i = 0; i < r; i++) {
        numerator = safe_multiply(numerator, n - i, p);
    }
    long long denominator = 1;
    for (long long i = 1; i <= r; i++) {
        denominator = safe_multiply(denominator, i, p);
    }
    return safe_multiply(numerator, modInverse(denominator, p), p);
}

int main(void) {
    long long n, r, p;
    if (scanf("%lld %lld %lld", &n, &r, &p) != 3) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    if (n < 0 || r < 0 || p <= 1) {
        fprintf(stderr, "Invalid parameters\n");
        return EXIT_FAILURE;
    }
    long long result = nCrModPFermat(n, r, p);
    printf("%lld\n", result);
    return EXIT_SUCCESS;
}