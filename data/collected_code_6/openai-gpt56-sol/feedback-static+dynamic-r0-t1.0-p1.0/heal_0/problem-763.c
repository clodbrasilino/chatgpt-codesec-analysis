#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

static int compare_int64(const void *lhs, const void *rhs)
{
    const int64_t a = *(const int64_t *)lhs;
    const int64_t b = *(const int64_t *)rhs;

    return (a > b) - (a < b);
}

static int find_minimum_difference(int64_t *array, size_t length, uint64_t *result)
{
    if (array == NULL || result == NULL || length < 2) {
        return -1;
    }

    qsort(array, length, sizeof(*array), compare_int64);

    uint64_t minimum = UINT64_MAX;

    for (size_t i = 1; i < length; ++i) {
        uint64_t difference = (uint64_t)array[i] - (uint64_t)array[i - 1];

        if (difference < minimum) {
            minimum = difference;
        }
    }

    *result = minimum;
    return 0;
}

int main(void)
{
    size_t length;

    if (scanf("%zu", &length) != 1 || length < 2 ||
        length > SIZE_MAX / sizeof(int64_t)) {
        fputs("Invalid array length\n", stderr);
        return EXIT_FAILURE;
    }

    int64_t *array = malloc(length * sizeof(*array));

    if (array == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (scanf("%" SCNd64, &array[i]) != 1) {
            fputs("Invalid array element\n", stderr);
            free(array);
            return EXIT_FAILURE;
        }
    }

    uint64_t minimum_difference;

    if (find_minimum_difference(array, length, &minimum_difference) != 0) {
        fputs("Unable to calculate minimum difference\n", stderr);
        free(array);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", minimum_difference);

    free(array);
    return EXIT_SUCCESS;
}