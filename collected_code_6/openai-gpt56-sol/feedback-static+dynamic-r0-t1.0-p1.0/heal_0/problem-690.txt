#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static int multiply_consecutive(const long long *values, size_t count,
                                long long *products)
{
    if (values == NULL || products == NULL || count < 2U) {
        return -1;
    }

    for (size_t i = 0U; i + 1U < count; ++i) {
        if (__builtin_mul_overflow(values[i], values[i + 1U], &products[i])) {
            return -1;
        }
    }

    return 0;
}

int main(void)
{
    size_t count;

    if (printf("Enter the number of values: ") < 0 ||
        scanf("%zu", &count) != 1 ||
        count < 2U ||
        count > SIZE_MAX / sizeof(long long)) {
        fputs("Invalid number of values.\n", stderr);
        return EXIT_FAILURE;
    }

    long long *values = malloc(count * sizeof(*values));
    if (values == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    size_t product_count = count - 1U;
    long long *products = malloc(product_count * sizeof(*products));
    if (products == NULL) {
        perror("malloc");
        free(values);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < count; ++i) {
        if (printf("Value %zu: ", i + 1U) < 0 ||
            scanf("%lld", &values[i]) != 1) {
            fputs("Invalid value.\n", stderr);
            free(products);
            free(values);
            return EXIT_FAILURE;
        }
    }

    if (multiply_consecutive(values, count, products) != 0) {
        fputs("Multiplication overflow or invalid input.\n", stderr);
        free(products);
        free(values);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < product_count; ++i) {
        if (printf("%lld%s", products[i],
                   i + 1U == product_count ? "\n" : " ") < 0) {
            free(products);
            free(values);
            return EXIT_FAILURE;
        }
    }

    free(products);
    free(values);
    return EXIT_SUCCESS;
}