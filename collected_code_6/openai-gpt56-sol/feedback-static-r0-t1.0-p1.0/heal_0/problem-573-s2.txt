#include <errno.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static int compare_ints(const void *lhs, const void *rhs)
{
    const int left = *(const int *)lhs;
    const int right = *(const int *)rhs;

    return (left > right) - (left < right);
}

static int multiply_checked(long long lhs, int rhs, long long *result)
{
    if (result == NULL) {
        return 0;
    }

    if (rhs > 0) {
        if (lhs > LLONG_MAX / rhs || lhs < LLONG_MIN / rhs) {
            return 0;
        }
    } else if (rhs < 0) {
        if (rhs == -1) {
            if (lhs == LLONG_MIN) {
                return 0;
            }
        } else if (lhs > LLONG_MIN / rhs || lhs < LLONG_MAX / rhs) {
            return 0;
        }
    }

    *result = lhs * rhs;
    return 1;
}

static int product_of_unique_numbers(const int *values, size_t count,
                                     long long *product)
{
    int *sorted = NULL;
    long long result = 1;
    size_t i;

    if (product == NULL || (values == NULL && count != 0U)) {
        return 0;
    }

    if (count == 0U) {
        *product = result;
        return 1;
    }

    if (count > SIZE_MAX / sizeof(*sorted)) {
        return 0;
    }

    sorted = malloc(count * sizeof(*sorted));
    if (sorted == NULL) {
        return 0;
    }

    for (i = 0U; i < count; ++i) {
        sorted[i] = values[i];
    }

    qsort(sorted, count, sizeof(*sorted), compare_ints);

    for (i = 0U; i < count; ++i) {
        if (i == 0U || sorted[i] != sorted[i - 1U]) {
            if (!multiply_checked(result, sorted[i], &result)) {
                free(sorted);
                return 0;
            }
        }
    }

    free(sorted);
    *product = result;
    return 1;
}

int main(void)
{
    size_t count;
    int *values = NULL;
    long long product;
    size_t i;

    if (scanf("%zu", &count) != 1) {
        fprintf(stderr, "Failed to read the list size.\n");
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(*values)) {
        fprintf(stderr, "The list is too large.\n");
        return EXIT_FAILURE;
    }

    if (count != 0U) {
        values = malloc(count * sizeof(*values));
        if (values == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            return EXIT_FAILURE;
        }
    }

    for (i = 0U; i < count; ++i) {
        if (scanf("%d", &values[i]) != 1) {
            fprintf(stderr, "Failed to read list element.\n");
            free(values);
            return EXIT_FAILURE;
        }
    }

    if (!product_of_unique_numbers(values, count, &product)) {
        fprintf(stderr, "Unable to calculate the product.\n");
        free(values);
        return EXIT_FAILURE;
    }

    if (printf("%lld\n", product) < 0) {
        fprintf(stderr, "Failed to write the result.\n");
        free(values);
        return EXIT_FAILURE;
    }

    free(values);
    return EXIT_SUCCESS;
}