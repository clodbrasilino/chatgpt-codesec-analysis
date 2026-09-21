#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

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

int64_t gcdExtended(int64_t a, int64_t b, int64_t *x, int64_t *y) {
    if (a == 0) {
        *x = 0;
        *y = 1;
        return b;
    }
    int64_t x1, y1;
    int64_t gcd = gcdExtended(b % a, a, &x1, &y1);
    *x = y1 - (b / a) * x1;
    *y = x1;
    return gcd;
}

int64_t modInverse(int64_t n, int64_t mod) {
    int64_t x, y;
    int64_t g = gcdExtended(n, mod, &x, &y);
    if (g != 1 && g != -1) {
        return 0;
    }
    int64_t res = (x % mod + mod) % mod;
    return res;
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
            int64_t inv = modInverse(den, p);
            if (inv == 0) {
                return 0;
            }
            res = mulmod(res, mulmod(num, inv, p), p);
            n /= p;
            r /= p;
        }
        return res;
    }

    if ((uint64_t)n > SIZE_MAX / sizeof(int64_t) - 1) {
        return -1;
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
    int64_t inv = modInverse(denominator, p);
    if (inv == 0) {
        free(fact);
        return 0;
    }
    int64_t result = mulmod(numerator, inv, p);

    free(fact);
    return result;
}

int main(void) {
    char line[4096];
    int64_t n, r, p;
    char *ptr;
    char *endptr;

    if (fgets(line, sizeof(line), stdin) == NULL) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    size_t len = strlen(line);
    if (len > 0 && line[len - 1] != '\n' && !feof(stdin)) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    ptr = line;
    errno = 0;
    n = strtoimax(ptr, &endptr, 10);
    if (endptr == ptr || errno == ERANGE) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    ptr = endptr;

    errno = 0;
    r = strtoimax(ptr, &endptr, 10);
    if (endptr == ptr || errno == ERANGE) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    ptr = endptr;

    errno = 0;
    p = strtoimax(ptr, &endptr, 10);
    if (endptr == ptr || errno == ERANGE) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    while (*endptr == ' ' || *endptr == '\t' || *endptr == '\n' || *endptr == '\r') {
        endptr++;
    }
    if (*endptr != '\0') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (p <= 1) {
        fprintf(stderr, "Modulus must be greater than 1\n");
        return EXIT_FAILURE;
    }

    if (n < 0 || r < 0) {
        fprintf(stderr, "n and r must be non-negative\n");
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