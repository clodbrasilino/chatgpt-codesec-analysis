#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>

static int compare_int64(const void *left, const void *right)
{
    const int64_t a = *(const int64_t *)left;
    const int64_t b = *(const int64_t *)right;

    return (a > b) - (a < b);
}

static int sum_absolute_differences(int64_t *values, size_t count, uint64_t *result)
{
    uint64_t prefix_sum = 0;
    uint64_t total = 0;

    if (values == NULL || result == NULL) {
        return -1;
    }

    qsort(values, count, sizeof(*values), compare_int64);

    for (size_t i = 0; i < count; ++i) {
        __int128 contribution =
            (__int128)values[i] * (__int128)i - (__int128)prefix_sum;
        __int128 next_total = (__int128)total + contribution;
        __int128 next_prefix = (__int128)prefix_sum + values[i];

        if (contribution < 0 || next_total > UINT64_MAX ||
            next_prefix < 0 || next_prefix > UINT64_MAX) {
            return -1;
        }

        total = (uint64_t)next_total;
        prefix_sum = (uint64_t)next_prefix;
    }

    *result = total;
    return 0;
}

int main(void)
{
    size_t count;
    int64_t *values = NULL;
    uint64_t result;

    if (scanf("%zu", &count) != 1) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(*values)) {
        fputs("Array size is too large\n", stderr);
        return EXIT_FAILURE;
    }

    if (count > 0) {
        values = malloc(count * sizeof(*values));
        if (values == NULL) {
            fputs("Memory allocation failed\n", stderr);
            return EXIT_FAILURE;
        }
    } else {
        puts("0");
        return EXIT_SUCCESS;
    }

    for (size_t i = 0; i < count; ++i) {
        if (scanf("%" SCNd64, &values[i]) != 1) {
            fputs("Invalid input\n", stderr);
            free(values);
            return EXIT_FAILURE;
        }
    }

    errno = 0;
    if (sum_absolute_differences(values, count, &result) != 0) {
        fputs("Result is out of range\n", stderr);
        free(values);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    free(values);
    return EXIT_SUCCESS;
}