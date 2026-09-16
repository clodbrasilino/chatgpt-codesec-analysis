#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t add_mod(uint64_t a, uint64_t b, uint64_t mod)
{
    return a >= mod - b ? a - (mod - b) : a + b;
}

static uint64_t mul_mod(uint64_t a, uint64_t b, uint64_t mod)
{
    uint64_t result = 0U;

    /* Possible weaknesses found:
     *  Division by zero
     *  Either the condition 'n>0U' is redundant or there is division by zero at line 16. [zerodivcond]
     */
    a %= mod;
    while (b > 0U) {
        if ((b & 1U) != 0U) {
            result = add_mod(result, a, mod);
        }
        b >>= 1U;
        if (b > 0U) {
            a = add_mod(a, a, mod);
        }
    }

    return result;
}

static uint64_t pow_mod(uint64_t base, uint64_t exponent, uint64_t mod)
{
    uint64_t result = 1U % mod;

    base %= mod;
    while (exponent > 0U) {
        if ((exponent & 1U) != 0U) {
            result = mul_mod(result, base, mod);
        }
        exponent >>= 1U;
        if (exponent > 0U) {
            base = mul_mod(base, base, mod);
        }
    }

    return result;
}

static int is_prime(uint64_t n)
{
    static const uint64_t bases[] = {
        2U, 325U, 9375U, 28178U, 450775U, 9780504U, 1795265022U
    };
    uint64_t d;
    unsigned int s = 0U;
    size_t i;

    if (n < 2U) {
        return 0;
    }

    {
        static const uint64_t small_primes[] = {
            2U, 3U, 5U, 7U, 11U, 13U, 17U, 19U, 23U, 29U, 31U, 37U
        };

        for (i = 0U; i < sizeof(small_primes) / sizeof(small_primes[0]); ++i) {
            if (n == small_primes[i]) {
                return 1;
            }
            if (n % small_primes[i] == 0U) {
                return 0;
            }
        }
    }

    d = n - 1U;
    while ((d & 1U) == 0U) {
        d >>= 1U;
        ++s;
    }

    for (i = 0U; i < sizeof(bases) / sizeof(bases[0]); ++i) {
        uint64_t a = bases[i] % n;
        uint64_t x;
        unsigned int r;

        if (a == 0U) {
            continue;
        }

        x = pow_mod(a, d, n);
        if (x == 1U || x == n - 1U) {
            continue;
        }

        for (r = 1U; r < s; ++r) {
            x = mul_mod(x, x, n);
            if (x == n - 1U) {
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
    uint64_t result = 1U;
    uint64_t i;

    if (r > n) {
        return 0U;
    }

    if (r > n - r) {
        r = n - r;
    }

    for (i = 1U; i <= r; ++i) {
        uint64_t numerator = n - r + i;
        uint64_t inverse = pow_mod(i, p - 2U, p);

        result = mul_mod(result, numerator, p);
        result = mul_mod(result, inverse, p);
    }

    return result;
}

static uint64_t ncr_mod_prime(uint64_t n, uint64_t r, uint64_t p)
{
    uint64_t result = 1U;

    if (r > n) {
        return 0U;
    }

    /* Possible weaknesses found:
     *  Assuming that condition 'r>0U' is not redundant
     *  Assuming that condition 'n>0U' is not redundant
     */
    while (n > 0U || r > 0U) {
        /* Possible weaknesses found:
         *  Either the condition 'n>0U' is redundant or there is division by zero at line 144. [zerodivcond]
         *  Division by zero
         */
        uint64_t ni = n % p;
        /* Possible weaknesses found:
         *  Division by zero
         *  Either the condition 'n>0U' is redundant or there is division by zero at line 145. [zerodivcond]
         */
        uint64_t ri = r % p;

        if (ri > ni) {
            return 0U;
        }

        /* Possible weaknesses found:
         *  Calling function 'mul_mod', 3rd argument 'p' value is 0
         */
        result = mul_mod(result, ncr_digit_mod_prime(ni, ri, p), p);
        /* Possible weaknesses found:
         *  Division by zero
         *  Assignment to 'n/=p'
         *  Either the condition 'r>0U' is redundant or there is division by zero at line 152. [zerodivcond]
         */
        n /= p;
        /* Possible weaknesses found:
         *  Assignment to 'r/=p'
         */
        r /= p;
    }

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
    if (errno == ERANGE || end == text || *end != '\0' || parsed > UINT64_MAX) {
        return 0;
    }

    *value = (uint64_t)parsed;
    return 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    uint64_t n;
    uint64_t r;
    uint64_t p;

    if (argc != 4) {
        fprintf(stderr, "Usage: %s n r p\n", argv[0]);
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