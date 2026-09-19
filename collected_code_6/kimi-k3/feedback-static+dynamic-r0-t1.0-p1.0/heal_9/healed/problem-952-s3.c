#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

static int64_t mul_mod(int64_t a, int64_t b, int64_t mod) {
    return (int64_t)(((unsigned __int128)(uint64_t)a * (unsigned __int128)(uint64_t)b) % (unsigned __int128)(uint64_t)mod);
}

static int64_t power(int64_t base, int64_t exp, int64_t mod) {
    int64_t result = 1 % mod;
    base %= mod;
    if (base < 0) {
        base += mod;
    }

    while (exp > 0) {
        if (exp & 1) {
            result = mul_mod(result, base, mod);
        }
        base = mul_mod(base, base, mod);
        exp >>= 1;
    }

    return result;
}

static int64_t modInverse(int64_t n, int64_t mod) {
    return power(n, mod - 2, mod);
}

static int64_t nCrModP(int64_t n, int64_t r, int64_t p) {
    if (r < 0 || r > n || n < 0) {
        return 0;
    }
    if (r == 0 || r == n) {
        return 1 % p;
    }
    if (r > n - r) {
        r = n - r;
    }

    int64_t *fact = (int64_t *)malloc((size_t)p * sizeof(int64_t));
    if (fact == NULL) {
        return -1;
    }

    fact[0] = 1 % p;
    for (int64_t i = 1; i < p; i++) {
        fact[i] = mul_mod(fact[i - 1], i, p);
    }

    int64_t result = 1 % p;
    while (n > 0 || r > 0) {
        int64_t ni = n % p;
        int64_t ri = r % p;
        if (ri > ni) {
            free(fact);
            return 0;
        }
        
        int64_t numerator = fact[ni];
        int64_t denominator = mul_mod(fact[ri], fact[ni - ri], p);
        int64_t digit_result = mul_mod(numerator, modInverse(denominator, p), p);
        
        result = mul_mod(result, digit_result, p);
        n /= p;
        r /= p;
    }
    
    free(fact);
    return result;
}

int main(void) {
    int64_t n, r, p;

    if (scanf("%" SCNd64 " %" SCNd64 " %" SCNd64, &n, &r, &p) != 3) {
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

    printf("%" PRId64 "\n", result);
    return EXIT_SUCCESS;
}