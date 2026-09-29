#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>

static int compare_int64(const void *lhs, const void *rhs)
{
    const int64_t a = *(const int64_t *)lhs;
    const int64_t b = *(const int64_t *)rhs;

    return (a > b) - (a < b);
}

static int sum_absolute_differences(int64_t *array, size_t length, uint64_t *result)
{
    uint64_t sum = 0;
    int64_t previous = 0;
    uint64_t prefix = 0;

    if (array == NULL || result == NULL) {
        return -1;
    }

    qsort(array, length, sizeof(*array), compare_int64);

    for (size_t i = 0; i < length; ++i) {
        uint64_t delta;
        uint64_t contribution;

        if (i == 0) {
            previous = array[i];
            continue;
        }

        delta = (uint64_t)array[i] - (uint64_t)previous;

        if (delta != 0 && i > UINT64_MAX / delta) {
            return -1;
        }

        contribution = delta * (uint64_t)i;

        if (prefix > UINT64_MAX - contribution ||
            sum > UINT64_MAX - prefix - contribution) {
            return -1;
        }

        prefix += contribution;
        sum += prefix;
        previous = array[i];
    }

    *result = sum;
    return 0;
}

int main(void)
{
    size_t length;
    int64_t *array = NULL;
    uint64_t result;

    if (scanf("%zu", &length) != 1) {
        fputs("Invalid array length\n", stderr);
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(*array)) {
        fputs("Array is too large\n", stderr);
        return EXIT_FAILURE;
    }

    if (length > 0) {
        array = malloc(length * sizeof(*array));
        if (array == NULL) {
            fputs("Memory allocation failed\n", stderr);
            return EXIT_FAILURE;
        }
    } else {
        printf("0\n");
        return EXIT_SUCCESS;
    }

    for (size_t i = 0; i < length; ++i) {
        if (scanf("%" SCNd64, &array[i]) != 1) {
            fputs("Invalid array element\n", stderr);
            free(array);
            return EXIT_FAILURE;
        }
    }

    errno = 0;
    if (sum_absolute_differences(array, length, &result) != 0) {
        fputs("Result exceeds supported range\n", stderr);
        free(array);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    free(array);

    return EXIT_SUCCESS;
}