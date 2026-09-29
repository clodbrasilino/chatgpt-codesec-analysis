#include <stdio.h>
#include <stdlib.h>

long long mod_exp(long long base, long long exp, long long mod) {
    long long res = 1;
    base = base % mod;
    if (base < 0) base += mod;
    while (exp > 0) {
        if (exp & 1) {
            res = (__int128)res * base % mod;
        }
        exp >>= 1;
        base = (__int128)base * base % mod;
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
    if (n >= p) {
        return (__int128)ncr_mod_p(n / p, r / p, p) * ncr_mod_p(n % p, r % p, p) % p;
    }
    long long numerator = 1;
    long long denominator = 1;
    for (long long i = 0; i < r; i++) {
        numerator = (__int128)numerator * (n - i) % p;
        denominator = (__int128)denominator * (i + 1) % p;
    }
    return (__int128)numerator * mod_exp(denominator, p - 2, p) % p;
}

int main(int argc, char const * const argv[]) {
    if (argc != 4) {
        printf("Usage: %s <n> <r> <p>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr;
    long long n = strtoll(argv[1], &endptr, 10);
    if (*endptr != '\0' || argv[1][0] == '\0') {
        printf("0\n");
        return EXIT_SUCCESS;
    }
    long long r = strtoll(argv[2], &endptr, 10);
    if (*endptr != '\0' || argv[2][0] == '\0') {
        printf("0\n");
        return EXIT_SUCCESS;
    }
    long long p = strtoll(argv[3], &endptr, 10);
    if (*endptr != '\0' || argv[3][0] == '\0') {
        printf("0\n");
        return EXIT_SUCCESS;
    }
    if (p <= 1) {
        printf("0\n");
        return EXIT_SUCCESS;
    }
    long long result = ncr_mod_p(n, r, p);
    printf("%lld\n", result);
    return EXIT_SUCCESS;
}