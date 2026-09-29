#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

static uint64_t add_mod(uint64_t a, uint64_t b, uint64_t modulus)
{
    return (a >= modulus - b) ? a - (modulus - b) : a + b;
}

static uint64_t multiply_mod(uint64_t a, uint64_t b, uint64_t modulus)
{
    uint64_t result = 0;

    a %= modulus;

    while (b != 0) {
        if ((b & UINT64_C(1)) != 0) {
            result = add_mod(result, a, modulus);
        }

        b >>= 1;

        if (b != 0) {
            a = add_mod(a, a, modulus);
        }
    }

    return result;
}

static int array_product_remainder(const uint64_t values[],
                                   size_t count,
                                   uint64_t modulus,
                                   uint64_t *remainder)
{
    uint64_t result;

    if (remainder == NULL || modulus == 0 || (values == NULL && count != 0)) {
        return -1;
    }

    result = UINT64_C(1) % modulus;

    for (size_t i = 0; i < count; ++i) {
        result = multiply_mod(result, values[i], modulus);
    }

    *remainder = result;
    return 0;
}

int main(void)
{
    uint64_t values[] = {
        UINT64_C(10000000000000000000),
        UINT64_C(9999999999999999999),
        UINT64_C(12345678901234567890)
    };
    const size_t count = sizeof values / sizeof values[0];
    const uint64_t modulus = UINT64_C(1000000007);
    uint64_t remainder;

    if (array_product_remainder(values, count, modulus, &remainder) != 0) {
        fputs("Unable to calculate the remainder.\n", stderr);
        return 1;
    }

    if (printf("%" PRIu64 "\n", remainder) < 0) {
        return 1;
    }

    return 0;
}