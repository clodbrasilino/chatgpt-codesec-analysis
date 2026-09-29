#include <stdio.h>
#include <stdlib.h>

long long power_mod(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

long long mod_inverse(long long a, long long p) {
    return power_mod(a, p - 2, p);
}

long long ncr_mod_p(long long n, long long r, long long p) {
    if (r > n) {
        return 0;
    }
    if (r == 0 || r == n) {
        return 1;
    }
    if (r > n - r) {
        r = n - r;
    }

    long long numerator = 1;
    long long denominator = 1;

    for (long long i = 0; i < r; i++) {
        numerator = (numerator * (n - i)) % p;
        denominator = (denominator * (i + 1)) % p;
    }

    return (numerator * mod_inverse(denominator, p)) % p;
}

int main(void) {
    long long n, r, p;

    if (scanf("%lld %lld %lld", &n, &r, &p) != 3) {
        return 1;
    }

    if (p <= 1) {
        return 1;
    }

    printf("%lld\n", ncr_mod_p(n, r, p));

    return 0;
}