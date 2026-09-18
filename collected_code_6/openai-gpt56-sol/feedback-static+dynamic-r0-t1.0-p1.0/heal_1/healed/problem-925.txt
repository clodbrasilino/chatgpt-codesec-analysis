#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int tuple_product(const long long *values, size_t count,
                         long long *product)
{
    if (values == NULL || product == NULL || count == 0U) {
        return -1;
    }

    long long result = 1;

    for (size_t i = 0U; i < count; ++i) {
        const long long value = values[i];

        if (value != 0) {
            if (result > 0) {
                if (value > 0) {
                    if (result > LLONG_MAX / value) {
                        return -1;
                    }
                } else if (value < LLONG_MIN / result) {
                    return -1;
                }
            } else if (result < 0) {
                if (value > 0) {
                    if (result < LLONG_MIN / value) {
                        return -1;
                    }
                } else if (value < LLONG_MAX / result) {
                    return -1;
                }
            }
        }

        result *= value;
    }

    *product = result;
    return 0;
}

int main(void)
{
    size_t count;

    if (scanf("%zu", &count) != 1 || count == 0U ||
        count > SIZE_MAX / sizeof(long long)) {
        fputs("Invalid tuple size.\n", stderr);
        return EXIT_FAILURE;
    }

    long long *values = malloc(count * sizeof(*values));
    if (values == NULL) {
        fputs("Memory allocation failed.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < count; ++i) {
        if (scanf("%lld", &values[i]) != 1) {
            fputs("Invalid tuple element.\n", stderr);
            free(values);
            return EXIT_FAILURE;
        }
    }

    long long product;
    if (tuple_product(values, count, &product) != 0) {
        fputs("Product overflow or invalid input.\n", stderr);
        free(values);
        return EXIT_FAILURE;
    }

    free(values);

    if (printf("%lld\n", product) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}