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

static uint64_t ncr_mod(uint64_t n, uint64_t r, uint64_t modulus)
{
    uint64_t result = 1U;

    if (modulus == 1U) {
        return 0U;
    }

    if (r > n) {
        return 0U;
    }

    if (r > n - r) {
        r = n - r;
    }

    for (uint64_t i = 1U; i <= r; ++i) {
        uint64_t numerator = n - r + i;
        uint64_t denominator = i;
        uint64_t divisor = gcd_u64(numerator, denominator);

        numerator /= divisor;
        denominator /= divisor;

        divisor = gcd_u64(result, denominator);
        result /= divisor;
        denominator /= divisor;

        if (denominator != 1U) {
            uint64_t j = i + 1U;

            while (denominator != 1U && j <= r) {
                uint64_t future = n - r + j;
                divisor = gcd_u64(future, denominator);
                denominator /= divisor;
                ++j;
            }

            if (denominator != 1U) {
                return 0U;
            }
        }

        result = multiply_mod(result, numerator % modulus, modulus);
    }

    return result;
}

int main(void)
{
    uint64_t n;
    uint64_t r;
    uint64_t p;

    if (scanf("%" SCNu64 " %" SCNu64 " %" SCNu64, &n, &r, &p) != 3) {
        return 1;
    }

    if (p == 0U) {
        return 1;
    }

    printf("%" PRIu64 "\n", ncr_mod(n, r, p));
    return 0;
}