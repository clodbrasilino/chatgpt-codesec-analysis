#include <stdio.h>
#include <stdlib.h>

unsigned long long power(unsigned long long x, unsigned long long y, unsigned long long p) {
    unsigned long long res = 1;
    x = x % p;
    while (y > 0) {
        if (y & 1)
            res = (res * x) % p;
        y = y >> 1;
        x = (x * x) % p;
    }
    return res;
}

unsigned long long modInverse(unsigned long long n, unsigned long long p) {
    if (p <= 1) return 0;
    return power(n, p - 2, p);
}

unsigned long long nCrModP_small(unsigned long long n, unsigned long long r, unsigned long long p) {
    if (r > n)
        return 0;
    if (r == 0 || r == n)
        return 1 % p;
    if (r > n - r)
        r = n - r;

    unsigned long long num = 1, den = 1;
    for (unsigned long long i = 0; i < r; i++) {
        num = (num * (n - i)) % p;
        den = (den * (i + 1)) % p;
    }
    return (num * modInverse(den, p)) % p;
}

unsigned long long nCrModP(unsigned long long n, unsigned long long r, unsigned long long p) {
    if (p <= 1)
        return 0;
    if (r > n)
        return 0;
    if (r == 0)
        return 1 % p;
    
    if (n >= p) {
        return (nCrModP(n / p, r / p, p) * nCrModP_small(n % p, r % p, p)) % p;
    }

    return nCrModP_small(n, r, p);
}

int main(void) {
    unsigned long long n, r, p;
    if (scanf("%llu %llu %llu", &n, &r, &p) == 3) {
        unsigned long long result = nCrModP(n, r, p);
        printf("%llu\n", result);
    }
    return 0;
}