#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int64_t power(int64_t base, int64_t exp, int64_t mod) {
    int64_t result = 1;
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

int64_t modInverse(int64_t n, int64_t mod) {
    return power(n, mod - 2, mod);
}

int64_t nCrModP(int64_t n, int64_t r, int64_t p) {
    if (r < 0 || r > n) {
        return 0;
    }
    if (r == 0 || r == n) {
        return 1;
    }
    if (r > n - r) {
        r = n - r;
    }
    
    int64_t *fact = (int64_t *)malloc((n + 1) * sizeof(int64_t));
    if (fact == NULL) {
        return -1;
    }
    
    fact[0] = 1;
    for (int64_t i = 1; i <= n; i++) {
        fact[i] = (fact[i - 1] * i) % p;
    }
    
    int64_t numerator = fact[n];
    int64_t denominator = (fact[r] * fact[n - r]) % p;
    int64_t result = (numerator * modInverse(denominator, p)) % p;
    
    free(fact);
    return result;
}

int main(void) {
    int64_t n, r, p;
    
    if (scanf("%lld %lld %lld", &n, &r, &p) != 3) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (p <= 1) {
        fprintf(stderr, "Modulus must be greater than 1\n");
        return EXIT_FAILURE;
    }
    
    int64_t result = nCrModP(n, r, p);
    if (result == -1) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    printf("%lld\n", result);
    return EXIT_SUCCESS;
}