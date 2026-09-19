#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

static int64_t mul_mod(int64_t a, int64_t b, int64_t mod) {
    return (int64_t)(((unsigned __int128)a * (unsigned __int128)b) % (unsigned __int128)mod);
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
 /* Possible weaknesses found:
  *  test case 1 failed: expected 11, got 0
  */

static int64_t nCrModP(int64_t n, int64_t r, int64_t p) {
    if (r < 0 || r > n) {
        return 0;
    }
    if (r == 0 || r == n) {
        return 1 % p;
    }
    if (r > n - r) {
        r = n - r;
    }

    int64_t *fact = (int64_t *)malloc((size_t)(n + 1) * sizeof(int64_t));
    if (fact == NULL) {
        return -1;
    }

    fact[0] = 1 % p;
    for (int64_t i = 1; i <= n; i++) {
        fact[i] = mul_mod(fact[i - 1], i, p);
    }

    int64_t numerator = fact[n];
    int64_t denominator = mul_mod(fact[r], fact[n - r], p);
    int64_t result = mul_mod(numerator, modInverse(denominator, p), p);

    free(fact);
    return result;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000002,time:1281,execs:470,op:havoc,rep:1; likely memory-safety defect
  */

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