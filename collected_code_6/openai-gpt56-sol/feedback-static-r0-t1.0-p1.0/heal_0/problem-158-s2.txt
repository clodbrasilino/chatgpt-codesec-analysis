#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

static int compare_int64(const void *left, const void *right)
{
    const int64_t a = *(const int64_t *)left;
    const int64_t b = *(const int64_t *)right;

    return (a > b) - (a < b);
}

static int calculate_operations(int64_t *values, size_t count, uint64_t *operations)
{
    if (values == NULL || operations == NULL || count == 0U) {
        return 0;
    }

    qsort(values, count, sizeof(*values), compare_int64);

    const int64_t target = values[count / 2U];
    uint64_t total = 0U;

    for (size_t i = 0U; i < count; ++i) {
        uint64_t difference;

        if (values[i] >= target) {
            difference = (uint64_t)values[i] - (uint64_t)target;
        } else {
            difference = (uint64_t)target - (uint64_t)values[i];
        }

        if (UINT64_MAX - total < difference) {
            return 0;
        }

        total += difference;
    }

    *operations = total;
    return 1;
}

int main(void)
{
    size_t count;

    if (scanf("%zu", &count) != 1 || count == 0U ||
        count > SIZE_MAX / sizeof(int64_t)) {
        return EXIT_FAILURE;
    }

    int64_t *values = malloc(count * sizeof(*values));
    if (values == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < count; ++i) {
        if (scanf("%" SCNd64, &values[i]) != 1) {
            free(values);
            return EXIT_FAILURE;
        }
    }

    uint64_t operations;
    if (!calculate_operations(values, count, &operations)) {
        free(values);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", operations) < 0) {
        free(values);
        return EXIT_FAILURE;
    }

    free(values);
    return EXIT_SUCCESS;
}