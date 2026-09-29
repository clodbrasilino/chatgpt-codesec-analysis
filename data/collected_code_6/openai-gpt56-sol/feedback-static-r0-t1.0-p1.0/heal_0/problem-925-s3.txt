#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

static int calculate_product(const long long *values, size_t count, long long *product)
{
    size_t i;
    long long result = 1;

    if (values == NULL || product == NULL || count == 0U) {
        return -1;
    }

    for (i = 0U; i < count; ++i) {
        if ((values[i] > 0 && (result > LLONG_MAX / values[i] ||
                               result < LLONG_MIN / values[i])) ||
            (values[i] < -1 && (result > LLONG_MIN / values[i] ||
                                result < LLONG_MAX / values[i])) ||
            (values[i] == -1 && result == LLONG_MIN)) {
            return -1;
        }
        result *= values[i];
    }

    *product = result;
    return 0;
}

int main(void)
{
    size_t count;
    size_t i;
    long long *values = NULL;
    long long product;

    if (scanf("%zu", &count) != 1 || count == 0U ||
        count > SIZE_MAX / sizeof(*values)) {
        fputs("Invalid tuple size\n", stderr);
        return EXIT_FAILURE;
    }

    values = malloc(count * sizeof(*values));
    if (values == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0U; i < count; ++i) {
        errno = 0;
        if (scanf("%lld", &values[i]) != 1 || errno == ERANGE) {
            fputs("Invalid tuple element\n", stderr);
            free(values);
            return EXIT_FAILURE;
        }
    }

    if (calculate_product(values, count, &product) != 0) {
        fputs("Product overflow or invalid input\n", stderr);
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