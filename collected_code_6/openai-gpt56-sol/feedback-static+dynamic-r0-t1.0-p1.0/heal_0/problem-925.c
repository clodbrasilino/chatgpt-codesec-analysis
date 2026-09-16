#include <errno.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static int tuple_product(const long long *values, size_t count, long long *product)
{
    if (values == NULL || product == NULL || count == 0U) {
        return -1;
    }

    long long result = 1;

    for (size_t i = 0U; i < count; ++i) {
        if ((values[i] > 0 && result > LLONG_MAX / values[i]) ||
            (values[i] < 0 && result > 0 && values[i] < LLONG_MIN / result) ||
            (values[i] < 0 && result < 0 && result < LLONG_MAX / values[i])) {
            return -1;
        }

        result *= values[i];
    }

    *product = result;
    return 0;
}

int main(void)
{
    size_t count = 0U;

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

    long long product = 0;
    if (tuple_product(values, count, &product) != 0) {
        fputs("Product overflow or invalid input.\n", stderr);
        free(values);
        return EXIT_FAILURE;
    }

    if (printf("%lld\n", product) < 0) {
        free(values);
        return EXIT_FAILURE;
    }

    free(values);
    return EXIT_SUCCESS;
}