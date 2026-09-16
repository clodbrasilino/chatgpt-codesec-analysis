#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>

static int compare_ints(const void *lhs, const void *rhs)
{
    const int a = *(const int *)lhs;
    const int b = *(const int *)rhs;

    return (a > b) - (a < b);
}

static int max_disjoint_pair_sum(const int *values, size_t count, int k,
                                 int64_t *result)
{
    int *sorted;
    size_t i;
    int64_t sum = 0;

    if (result == NULL || (values == NULL && count != 0U) || k < 0) {
        return 0;
    }

    *result = 0;

    if (count < 2U) {
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

    i = count;
    while (i >= 2U) {
        int64_t larger = sorted[i - 1U];
        int64_t smaller = sorted[i - 2U];

        if (larger - smaller < (int64_t)k) {
            int64_t pair_sum = larger + smaller;

            if (pair_sum > 0) {
                sum += pair_sum;
            }
            i -= 2U;
        } else {
            --i;
        }
    }

    free(sorted);
    *result = sum;
    return 1;
}

int main(void)
{
    size_t count;
    int k;
    int *values = NULL;
    int64_t result;
    size_t i;

    if (scanf("%zu %d", &count, &k) != 2 || k < 0) {
        return EXIT_FAILURE;
    }

    if (count > 0U) {
        if (count > SIZE_MAX / sizeof(*values)) {
            return EXIT_FAILURE;
        }

        values = malloc(count * sizeof(*values));
        if (values == NULL) {
            return EXIT_FAILURE;
        }

        for (i = 0U; i < count; ++i) {
            if (scanf("%d", &values[i]) != 1) {
                free(values);
                return EXIT_FAILURE;
            }
        }
    }

    if (!max_disjoint_pair_sum(values, count, k, &result)) {
        free(values);
        return EXIT_FAILURE;
    }

    free(values);

    if (printf("%" PRId64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}