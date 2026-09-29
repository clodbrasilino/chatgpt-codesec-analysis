#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

int64_t mulmod(int64_t a, int64_t b, int64_t mod) {
#if defined(__SIZEOF_INT128__)
    __int128 res = (__int128)a * b;
    res %= mod;
    if (res < 0) res += mod;
    return (int64_t)res;
#else
    int64_t res = 0;
    a %= mod;
    if (a < 0) a += mod;
    b %= mod;
    if (b < 0) b += mod;
    while (b > 0) {
        if (b & 1) {
            res = (res + a) % mod;
        }
        a = (a * 2) % mod;
        b >>= 1;
    }
    return res;
#endif
}

int64_t power(int64_t base, int64_t exp, int64_t mod) {
    int64_t result = 1;
    base %= mod;
    if (base < 0) base += mod;
    while (exp > 0) {
        if (exp & 1) {
            result = mulmod(result, base, mod);
        }
        base = mulmod(base, base, mod);
        exp >>= 1;
    }
    return result;
}

int64_t modInverse(int64_t n, int64_t mod) {
    int64_t t = 0, newt = 1;
    int64_t r = mod, newr = n;
    while (newr != 0) {
        int64_t quotient = r / newr;
        int64_t temp = newt;
        newt = t - quotient * newt;
        t = temp;
        temp = newr;
        newr = r - quotient * newr;
        r = temp;
    }
    if (r > 1) return 0;
    if (t < 0) t += mod;
    return t;
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

    if (n >= p) {
        int64_t res = 1;
        while (n > 0 || r > 0) {
            int64_t ni = n % p;
            int64_t ri = r % p;
            if (ri > ni) {
                return 0;
            }
            int64_t num = 1, den = 1;
            for (int64_t i = 0; i < ri; i++) {
                num = mulmod(num, ni - i, p);
                den = mulmod(den, i + 1, p);
            }
            res = mulmod(res, mulmod(num, modInverse(den, p), p), p);
            n /= p;
            r /= p;
        }
        return res;
    }

    int64_t *fact = (int64_t *)malloc((size_t)(n + 1) * sizeof(int64_t));
    if (fact == NULL) {
        return -1;
    }

    fact[0] = 1;
    for (int64_t i = 1; i <= n; i++) {
        fact[i] = mulmod(fact[i - 1], i, p);
    }

    int64_t numerator = fact[n];
    int64_t denominator = mulmod(fact[r], fact[n - r], p);
    int64_t result = mulmod(numerator, modInverse(denominator, p), p);

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