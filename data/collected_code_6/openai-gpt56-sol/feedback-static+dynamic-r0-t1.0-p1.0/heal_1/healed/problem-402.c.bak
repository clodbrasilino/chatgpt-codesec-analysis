#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>

static uint64_t add_mod(uint64_t a, uint64_t b, uint64_t modulus)
{
    return (a >= modulus - b) ? a - (modulus - b) : a + b;
}

static uint64_t multiply_mod(uint64_t a, uint64_t b, uint64_t modulus)
{
    uint64_t result = 0;

    a %= modulus;

    while (b != 0) {
        if ((b & 1U) != 0) {
            result = add_mod(result, a, modulus);
        }

        b >>= 1U;

        if (b != 0) {
            a = add_mod(a, a, modulus);
        }
    }

    return result;
}

static uint64_t ncr_mod(uint64_t n, uint64_t r, uint64_t modulus)
{
    if (modulus == 1 || r > n) {
        return 0;
    }

    if (r > n - r) {
        r = n - r;
    }

    if (r == 0) {
        return 1 % modulus;
    }

    if (r > (uint64_t)(SIZE_MAX / sizeof(uint64_t))) {
        return 0;
    }

    size_t count = (size_t)r;
    uint64_t *factors = malloc(count * sizeof(*factors));

    if (factors == NULL) {
        return 0;
    }

    for (size_t i = 0; i < count; ++i) {
        factors[i] = n - r + (uint64_t)i + 1;
    }

    for (uint64_t denominator = 2; denominator <= r; ++denominator) {
        uint64_t remaining = denominator;

        for (size_t i = 0; i < count && remaining != 1; ++i) {
            uint64_t a = factors[i];
            uint64_t b = remaining;

            while (b != 0) {
                uint64_t t = a % b;
                a = b;
                b = t;
            }

            factors[i] /= a;
            remaining /= a;
        }

        if (remaining != 1) {
            free(factors);
            return 0;
        }
    }

    uint64_t result = 1 % modulus;

    for (size_t i = 0; i < count; ++i) {
        result = multiply_mod(result, factors[i] % modulus, modulus);
    }

    free(factors);
    return result;
}

int main(void)
{
    uint64_t n;
    uint64_t r;
    uint64_t modulus;

    if (scanf("%" SCNu64 " %" SCNu64 " %" SCNu64,
              &n, &r, &modulus) != 3) {
        return 1;
    }

    if (modulus == 0) {
        return 1;
    }

    printf("%" PRIu64 "\n", ncr_mod(n, r, modulus));
    return 0;
}