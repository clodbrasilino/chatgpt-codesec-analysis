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
    while (b != 0U) {
        if ((b & 1U) != 0U) {
            result = add_mod(result, a, modulus);
        }
        b >>= 1U;
        if (b != 0U) {
            a = add_mod(a, a, modulus);
        }
    }

    return result;
}

static int ncr_mod(uint64_t n, uint64_t r, uint64_t modulus, uint64_t *result)
{
    uint64_t value = 1U;
    uint64_t i;

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

    for (i = 1U; i <= r; ++i) {
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
        while (denominator != 1U) {
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
    uint64_t n;
    uint64_t r;
    uint64_t p;
    uint64_t result;

    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNu64 " %" SCNu64 " %" SCNu64, &n, &r, &p) != 3) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    if (!ncr_mod(n, r, p, &result)) {
        fputs("Computation failed\n", stderr);
        return 1;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return 1;
    }

    return 0;
}