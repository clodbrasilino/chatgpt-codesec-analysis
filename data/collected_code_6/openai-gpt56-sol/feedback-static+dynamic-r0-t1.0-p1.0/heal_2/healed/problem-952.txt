#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t add_mod(uint64_t a, uint64_t b, uint64_t mod)
{
    if (mod == UINT64_C(0)) {
        return UINT64_C(0);
    }

    a %= mod;
    b %= mod;

    return a >= mod - b ? a - (mod - b) : a + b;
}

static uint64_t mul_mod(uint64_t a, uint64_t b, uint64_t mod)
{
    uint64_t result = UINT64_C(0);

    if (mod == UINT64_C(0)) {
        return UINT64_C(0);
    }

    a %= mod;

    while (b != UINT64_C(0)) {
        if ((b & UINT64_C(1)) != UINT64_C(0)) {
            result = add_mod(result, a, mod);
        }

        b >>= 1U;

        if (b != UINT64_C(0)) {
            a = add_mod(a, a, mod);
        }
    }

    return result;
}

static uint64_t pow_mod(uint64_t base, uint64_t exponent, uint64_t mod)
{
    uint64_t result;

    if (mod == UINT64_C(0)) {
        return UINT64_C(0);
    }

    result = UINT64_C(1) % mod;
    base %= mod;

    while (exponent != UINT64_C(0)) {
        if ((exponent & UINT64_C(1)) != UINT64_C(0)) {
            result = mul_mod(result, base, mod);
        }

        exponent >>= 1U;

        if (exponent != UINT64_C(0)) {
            base = mul_mod(base, base, mod);
        }
    }

    return result;
}

static int is_prime(uint64_t n)
{
    static const uint64_t small_primes[] = {
        UINT64_C(2), UINT64_C(3), UINT64_C(5), UINT64_C(7),
        UINT64_C(11), UINT64_C(13), UINT64_C(17), UINT64_C(19),
        UINT64_C(23), UINT64_C(29), UINT64_C(31), UINT64_C(37)
    };
    static const uint64_t bases[] = {
        UINT64_C(2), UINT64_C(325), UINT64_C(9375),
        UINT64_C(28178), UINT64_C(450775), UINT64_C(9780504),
        UINT64_C(1795265022)
    };
    uint64_t d;
    unsigned int s = 0U;
    size_t i;

    if (n < UINT64_C(2)) {
        return 0;
    }

    for (i = 0U; i < sizeof small_primes / sizeof small_primes[0]; ++i) {
        if (n == small_primes[i]) {
            return 1;
        }

        if (n % small_primes[i] == UINT64_C(0)) {
            return 0;
        }
    }

    d = n - UINT64_C(1);

    while ((d & UINT64_C(1)) == UINT64_C(0)) {
        d >>= 1U;
        ++s;
    }

    for (i = 0U; i < sizeof bases / sizeof bases[0]; ++i) {
        const uint64_t a = bases[i] % n;
        uint64_t x;
        unsigned int r;

        if (a == UINT64_C(0)) {
            continue;
        }

        x = pow_mod(a, d, n);

        if (x == UINT64_C(1) || x == n - UINT64_C(1)) {
            continue;
        }

        for (r = 1U; r < s; ++r) {
            x = mul_mod(x, x, n);

            if (x == n - UINT64_C(1)) {
                break;
            }
        }

        if (r == s) {
            return 0;
        }
    }

    return 1;
}

static uint64_t ncr_digit_mod_prime(uint64_t n, uint64_t r, uint64_t p)
{
    uint64_t result = UINT64_C(1);
    uint64_t i;

    if (p < UINT64_C(2) || r > n) {
        return UINT64_C(0);
    }

    if (r > n - r) {
        r = n - r;
    }

    for (i = UINT64_C(1); i <= r; ++i) {
        const uint64_t numerator = n - r + i;
        const uint64_t inverse = pow_mod(i, p - UINT64_C(2), p);

        result = mul_mod(result, numerator, p);
        result = mul_mod(result, inverse, p);
    }

    return result;
}

static uint64_t ncr_mod_prime(uint64_t n, uint64_t r, uint64_t p)
{
    uint64_t result = UINT64_C(1);

    if (p < UINT64_C(2) || r > n) {
        return UINT64_C(0);
    }

    do {
        const uint64_t ni = n % p;
        const uint64_t ri = r % p;

        if (ri > ni) {
            return UINT64_C(0);
        }

        result = mul_mod(result, ncr_digit_mod_prime(ni, ri, p), p);
        n /= p;
        r /= p;
    } while (n != UINT64_C(0));

    return result;
}

static int parse_uint64(const char *text, uint64_t *value)
{
    char *end = NULL;
    uintmax_t parsed;

    if (text == NULL || value == NULL || *text == '\0' || *text == '-') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed > UINT64_MAX) {
        return 0;
    }

    *value = (uint64_t)parsed;
    return 1;
}

int main(int argc, char *const argv[])
{
    uint64_t n;
    uint64_t r;
    uint64_t p;

    if (argc != 4) {
        fprintf(stderr, "Usage: %s n r p\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    if (!parse_uint64(argv[1], &n) ||
        !parse_uint64(argv[2], &r) ||
        !parse_uint64(argv[3], &p)) {
        fputs("Invalid unsigned integer input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!is_prime(p)) {
        fputs("p must be prime\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", ncr_mod_prime(n, r, p)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}