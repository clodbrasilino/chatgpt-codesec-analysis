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
    uint64_t result = 0;

    /* Possible weaknesses found:
     *  Division by zero
     *  Either the condition 'n!=0U' is redundant or there is division by zero at line 16. [zerodivcond]
     */
    a %= mod;
    while (b != 0) {
        if ((b & 1U) != 0U) {
            result = add_mod(result, a, mod);
        }
        b >>= 1U;
        if (b != 0) {
            a = add_mod(a, a, mod);
        }
    }

    return result;
}

static uint64_t pow_mod(uint64_t base, uint64_t exponent, uint64_t mod)
{
    uint64_t result = 1U % mod;

    base %= mod;
    while (exponent != 0) {
        if ((exponent & 1U) != 0U) {
            result = mul_mod(result, base, mod);
        }
        exponent >>= 1U;
        if (exponent != 0) {
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
    unsigned int s = 0;

    if (n < 2U) {
        return 0;
    }

    for (uint64_t divisor = 2U; divisor <= 37U; ++divisor) {
        int divisor_is_prime = divisor == 2U || divisor == 3U ||
                               divisor == 5U || divisor == 7U ||
                               divisor == 11U || divisor == 13U ||
                               divisor == 17U || divisor == 19U ||
                               divisor == 23U || divisor == 29U ||
                               divisor == 31U || divisor == 37U;

        if (divisor_is_prime && n % divisor == 0U) {
            return n == divisor;
        }
    }

    d = n - 1U;
    while ((d & 1U) == 0U) {
        d >>= 1U;
        ++s;
    }

    for (size_t i = 0; i < sizeof(bases) / sizeof(bases[0]); ++i) {
        uint64_t a = bases[i] % n;
        uint64_t x;

        if (a == 0U) {
            continue;
        }

        x = pow_mod(a, d, n);
        if (x == 1U || x == n - 1U) {
            continue;
        }

        unsigned int r;
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

    if (r > n) {
        return 0U;
    }

    if (r > n - r) {
        r = n - r;
    }

    for (uint64_t i = 1U; i <= r; ++i) {
        uint64_t numerator = n - r + i;
        uint64_t inverse = pow_mod(i, p - 2U, p);

        result = mul_mod(result, numerator % p, p);
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
     *  Assuming that condition 'r!=0U' is not redundant
     *  Assuming that condition 'n!=0U' is not redundant
     */
    while (n != 0U || r != 0U) {
        /* Possible weaknesses found:
         *  Division by zero
         *  Either the condition 'n!=0U' is redundant or there is division by zero at line 140. [zerodivcond]
         */
        uint64_t ni = n % p;
        /* Possible weaknesses found:
         *  Either the condition 'n!=0U' is redundant or there is division by zero at line 141. [zerodivcond]
         *  Division by zero
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
         *  Either the condition 'r!=0U' is redundant or there is division by zero at line 148. [zerodivcond]
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
    uint64_t result;

    if (argc != 4) {
        (void)fprintf(stderr, "Usage: %s n r p\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (!parse_uint64(argv[1], &n) ||
        !parse_uint64(argv[2], &r) ||
        !parse_uint64(argv[3], &p)) {
        (void)fprintf(stderr, "Invalid unsigned integer input\n");
        return EXIT_FAILURE;
    }

    if (!is_prime(p)) {
        (void)fprintf(stderr, "p must be prime\n");
        return EXIT_FAILURE;
    }

    result = ncr_mod_prime(n, r, p);
    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}