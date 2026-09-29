#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

int multiply_adjacent(const int *values, size_t count, long long **products, size_t *product_count)
{
    long long *result;
    size_t i;

    if (values == NULL || products == NULL || product_count == NULL || count < 2) {
        return -1;
    }

    if (count - 1 > SIZE_MAX / sizeof(*result)) {
        return -1;
    }

    result = malloc((count - 1) * sizeof(*result));
    if (result == NULL) {
        return -1;
    }

    for (i = 0; i + 1 < count; ++i) {
        result[i] = (long long)values[i] * (long long)values[i + 1];
    }

    *products = result;
    *product_count = count - 1;
    return 0;
}

int main(void)
{
    const int tuple[] = {1, 5, 7, 8, 10};
    const size_t count = sizeof(tuple) / sizeof(tuple[0]);
    long long *products = NULL;
    size_t product_count = 0;
    size_t i;

    if (multiply_adjacent(tuple, count, &products, &product_count) != 0) {
        fputs("Unable to multiply adjacent elements.\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0; i < product_count; ++i) {
        if (printf("%lld%s", products[i], i + 1 < product_count ? " " : "\n") < 0) {
            free(products);
            return EXIT_FAILURE;
        }
    }

    free(products);
    return EXIT_SUCCESS;
}