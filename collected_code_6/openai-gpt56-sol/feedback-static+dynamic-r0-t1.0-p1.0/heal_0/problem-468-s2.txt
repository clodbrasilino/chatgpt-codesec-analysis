#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static int checked_multiply(long long a, long long b, long long *result)
{
    if (result == NULL) {
        return 0;
    }

    if (a > 0) {
        if ((b > 0 && a > LLONG_MAX / b) ||
            (b < 0 && b < LLONG_MIN / a)) {
            return 0;
        }
    } else if (a < 0) {
        if ((b > 0 && a < LLONG_MIN / b) ||
            (b < 0 && a < LLONG_MAX / b)) {
            return 0;
        }
    }

    *result = a * b;
    return 1;
}

static int maximum_increasing_subsequence_product(
    const long long *values,
    size_t count,
    long long *maximum_product)
{
    long long *products = NULL;
    long long best;
    size_t i;
    size_t j;

    if (values == NULL || maximum_product == NULL || count == 0 ||
        count > SIZE_MAX / sizeof(*products)) {
        return 0;
    }

    products = malloc(count * sizeof(*products));
    if (products == NULL) {
        return 0;
    }

    best = values[0];

    for (i = 0; i < count; ++i) {
        products[i] = values[i];

        for (j = 0; j < i; ++j) {
            long long candidate;

            if (values[j] < values[i] &&
                checked_multiply(products[j], values[i], &candidate) &&
                candidate > products[i]) {
                products[i] = candidate;
            }
        }

        if (products[i] > best) {
            best = products[i];
        }
    }

    free(products);
    *maximum_product = best;
    return 1;
}

int main(void)
{
    long long *values = NULL;
    long long result;
    unsigned long long input_count;
    size_t count;
    size_t i;

    if (scanf("%llu", &input_count) != 1 ||
        input_count == 0 ||
        input_count > SIZE_MAX ||
        input_count > SIZE_MAX / sizeof(*values)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    count = (size_t)input_count;
    values = malloc(count * sizeof(*values));
    if (values == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; ++i) {
        if (scanf("%lld", &values[i]) != 1) {
            fputs("Invalid input\n", stderr);
            free(values);
            return EXIT_FAILURE;
        }
    }

    if (!maximum_increasing_subsequence_product(values, count, &result)) {
        fputs("Unable to compute result\n", stderr);
        free(values);
        return EXIT_FAILURE;
    }

    if (printf("%lld\n", result) < 0) {
        free(values);
        return EXIT_FAILURE;
    }

    free(values);
    return EXIT_SUCCESS;
}