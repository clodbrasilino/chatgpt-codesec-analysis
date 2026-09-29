#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

int64_t power(int64_t base, int64_t exp, int64_t mod) {
    int64_t result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) {
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: -3650239320 * 7087220170 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000001,time:9723,execs:2369,op:havoc,rep:3)
             * UBSan: signed integer overflow: 2139910444410 * 5973102371287 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000001,time:9702,execs:2350,op:havoc,rep:3)
             * UBSan: signed integer overflow: 30240 * 836232702197760000 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000003,sig:06,src:000001,time:18413,execs:11333,op:havoc,rep:6)
             * UBSan: signed integer overflow: -8030991652943528 * 17490402327904324 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000002,sig:06,src:000001,time:12018,execs:4742,op:havoc,rep:3)
             */
            result = (result * base) % mod;
        }
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 6502809600 * 6502809600 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000001,time:9702,execs:2350,op:havoc,rep:3)
         * UBSan: signed integer overflow: 836232702197760000 * 836232702197760000 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000003,sig:06,src:000001,time:18413,execs:11333,op:havoc,rep:6)
         * UBSan: signed integer overflow: 11921405226426640 * 11921405226426640 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000002,sig:06,src:000001,time:12018,execs:4742,op:havoc,rep:3)
         * UBSan: signed integer overflow: 6760848990 * 6760848990 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000001,time:9723,execs:2369,op:havoc,rep:3)
         */
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

int64_t modInverse(int64_t n, int64_t mod) {
    return power(n, mod - 2, mod);
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected 11, got 0
  */

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

    if (n >= p) {
        return 0;
    }

    int64_t *fact = (int64_t *)malloc((size_t)(n + 1) * sizeof(int64_t));
    if (fact == NULL) {
        return -1;
    }

    fact[0] = 1;
    for (int64_t i = 1; i <= n; i++) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 21438530289717322 * 437 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000002,sig:06,src:000001,time:12018,execs:4742,op:havoc,rep:3)
         */
        fact[i] = (fact[i - 1] * i) % p;
    }

    int64_t numerator = fact[n];
    int64_t denominator = (fact[r] * fact[n - r]) % p;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 3628800 * 5224655796501 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000001,time:9702,execs:2350,op:havoc,rep:3)
     * UBSan: signed integer overflow: 9067403940 * -10960550110 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000001,time:9723,execs:2369,op:havoc,rep:3)
     * UBSan: signed integer overflow: -20984640813878922 * 9228925565628926 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000002,sig:06,src:000001,time:12018,execs:4742,op:havoc,rep:3)
     */
    int64_t result = (numerator * modInverse(denominator, p)) % p;

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