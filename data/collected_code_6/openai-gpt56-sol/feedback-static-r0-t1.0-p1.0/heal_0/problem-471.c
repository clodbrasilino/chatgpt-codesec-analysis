#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
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
        if ((b & 1U) != 0U) {
            result = add_mod(result, a, modulus);
        }

        b >>= 1U;

        if (b != 0) {
            a = add_mod(a, a, modulus);
        }
    }

    return result;
}

static int array_product_remainder(const uint64_t *values, size_t count,
                                   uint64_t modulus, uint64_t *remainder)
{
    uint64_t result;

    if (remainder == NULL || modulus == 0 || (values == NULL && count != 0)) {
        return -1;
    }

    result = 1U % modulus;

    for (size_t i = 0; i < count; ++i) {
        result = multiply_mod(result, values[i], modulus);
    }

    *remainder = result;
    return 0;
}

int main(void)
{
    size_t count;
    uint64_t modulus;
    uint64_t remainder;
    uint64_t *values = NULL;

    if (scanf("%zu %" SCNu64, &count, &modulus) != 2 || modulus == 0) {
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(*values)) {
        return EXIT_FAILURE;
    }

    if (count != 0) {
        values = malloc(count * sizeof(*values));
        if (values == NULL) {
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        if (scanf("%" SCNu64, &values[i]) != 1) {
            free(values);
            return EXIT_FAILURE;
        }
    }

    if (array_product_remainder(values, count, modulus, &remainder) != 0) {
        free(values);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", remainder) < 0) {
        free(values);
        return EXIT_FAILURE;
    }

    free(values);
    return EXIT_SUCCESS;
}