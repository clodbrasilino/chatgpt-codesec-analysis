#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

static uint64_t gcd_u64(uint64_t a, uint64_t b)
{
    while (b != 0U) {
        uint64_t remainder = a % b;
        a = b;
        b = remainder;
    }

    return a;
}

static uint64_t add_mod(uint64_t a, uint64_t b, uint64_t modulus)
{
    return (a >= modulus - b) ? a - (modulus - b) : a + b;
}

static uint64_t multiply_mod(uint64_t a, uint64_t b, uint64_t modulus)
{
    uint64_t result = 0U;

    a %= modulus;
    b %= modulus;

    while (b != 0U) {
        if ((b & UINT64_C(1)) != 0U) {
            result = add_mod(result, a, modulus);
        }

        b >>= 1U;

        if (b != 0U) {
            a = add_mod(a, a, modulus);
        }
    }

    return result;
}

static int ncr_mod(uint64_t n, uint64_t r, uint64_t modulus,
                   uint64_t *result)
{
    uint64_t value = UINT64_C(1);

    if (result == NULL || modulus == 0U || n > (uint64_t)INT64_MAX) {
        return 0;
    }

    if (r > n) {
        *result = 0U;
        return 1;
    }

    if (r > n - r) {
        r = n - r;
    }

    for (uint64_t i = UINT64_C(1); i <= r; ++i) {
        uint64_t numerator = n - r + i;
        uint64_t denominator = i;
        uint64_t divisor;
        uint64_t candidate;

        divisor = gcd_u64(numerator, denominator);
        numerator /= divisor;
        denominator /= divisor;

        divisor = gcd_u64(value, denominator);
        value /= divisor;
        denominator /= divisor;

        candidate = numerator;

        while (denominator != UINT64_C(1)) {
            if (candidate > UINT64_MAX - numerator) {
                return 0;
            }

            candidate += numerator;
            divisor = gcd_u64(candidate, denominator);
            candidate /= divisor;
            denominator /= divisor;
        }

        value = multiply_mod(value, candidate % modulus, modulus);
    }

    *result = value % modulus;
    return 1;
}

int main(void)
{
    char input[256];
    uint64_t n;
    uint64_t r;
    uint64_t modulus;
    uint64_t result;
    char extra;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    if (sscanf(input,
               " %" SCNu64 " %" SCNu64 " %" SCNu64 " %c",
               &n, &r, &modulus, &extra) != 3) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    if (!ncr_mod(n, r, modulus, &result)) {
        fputs("Computation failed\n", stderr);
        return 1;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return 1;
    }

    return 0;
}