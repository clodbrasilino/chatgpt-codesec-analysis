#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>

static int compare_int64(const void *lhs, const void *rhs)
{
    const int64_t a = *(const int64_t *)lhs;
    const int64_t b = *(const int64_t *)rhs;

    return (a > b) - (a < b);
}

static int minimum_difference(const int64_t *array, size_t count, uint64_t *result)
{
    int64_t *copy;
    uint64_t minimum;

    if (array == NULL || result == NULL || count < 2 ||
        count > SIZE_MAX / sizeof(*copy)) {
        return -1;
    }

    copy = malloc(count * sizeof(*copy));
    if (copy == NULL) {
        return -1;
    }

    for (size_t i = 0; i < count; ++i) {
        copy[i] = array[i];
    }

    qsort(copy, count, sizeof(*copy), compare_int64);

    minimum = (uint64_t)copy[1] - (uint64_t)copy[0];

    for (size_t i = 2; i < count; ++i) {
        const uint64_t difference = (uint64_t)copy[i] - (uint64_t)copy[i - 1];

        if (difference < minimum) {
            minimum = difference;
        }
    }

    free(copy);
    *result = minimum;
    return 0;
}

int main(void)
{
    int64_t values[] = {8, 3, 15, 1, 9};
    const size_t count = sizeof(values) / sizeof(values[0]);
    uint64_t result;

    if (minimum_difference(values, count, &result) != 0) {
        fputs("Unable to determine the minimum difference.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Minimum difference: %" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}