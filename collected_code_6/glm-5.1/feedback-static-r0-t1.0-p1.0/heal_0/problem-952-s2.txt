#include <stdio.h>
#include <stdlib.h>

long long mod_exp(long long base, long long exp, long long mod) {
    long long res = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            res = (res * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return res;
}

long long ncr_mod_p(long long n, long long r, long long p) {
    if (r < 0 || r > n) {
        return 0;
    }
    if (r == 0 || r == n) {
        return 1;
    }
    if (p == 1) {
        return 0;
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
    return (numerator * mod_exp(denominator, p - 2, p)) % p;
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <n> <r> <p>\n", argv[0]);
        return EXIT_FAILURE;
    }
    long long n = strtoll(argv[1], NULL, 10);
    long long r = strtoll(argv[2], NULL, 10);
    long long p = strtoll(argv[3], NULL, 10);
    if (p <= 1) {
        fprintf(stderr, "Error: p must be a prime greater than 1.\n");
        return EXIT_FAILURE;
    }
    long long result = ncr_mod_p(n, r, p);
    printf("%lld\n", result);
    return EXIT_SUCCESS;
}