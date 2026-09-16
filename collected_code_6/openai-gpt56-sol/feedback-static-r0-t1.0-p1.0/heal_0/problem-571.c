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

static int64_t maximum_pair_sum(int *values, size_t count, int k)
{
    int64_t sum = 0;
    size_t i;

    if (values == NULL || count < 2U || k < 0) {
        return 0;
    }

    qsort(values, count, sizeof(*values), compare_ints);
    i = count;

    while (i >= 2U) {
        const int64_t larger = values[i - 1U];
        const int64_t smaller = values[i - 2U];

        if (larger - smaller < (int64_t)k) {
            sum += larger + smaller;
            i -= 2U;
        } else {
            --i;
        }
    }

    return sum;
}

int main(void)
{
    size_t count;
    int k;
    int *values = NULL;

    if (scanf("%zu %d", &count, &k) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(*values)) {
        fprintf(stderr, "Input is too large\n");
        return EXIT_FAILURE;
    }

    if (count > 0U) {
        values = malloc(count * sizeof(*values));
        if (values == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        if (scanf("%d", &values[i]) != 1) {
            fprintf(stderr, "Invalid input\n");
            free(values);
            return EXIT_FAILURE;
        }
    }

    printf("%" PRId64 "\n", maximum_pair_sum(values, count, k));
    free(values);

    return EXIT_SUCCESS;
}