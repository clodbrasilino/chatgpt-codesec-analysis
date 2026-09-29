#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>

static int compare_int64(const void *lhs, const void *rhs)
{
    const int64_t a = *(const int64_t *)lhs;
    const int64_t b = *(const int64_t *)rhs;

    return (a > b) - (a < b);
}

static int sum_absolute_differences(int64_t *array, size_t length,
                                    uint64_t *result)
{
    uint64_t sum = 0;
    uint64_t prefix = 0;
    int64_t previous;

    if (result == NULL || (array == NULL && length != 0)) {
        return -1;
    }

    if (length == 0) {
        *result = 0;
        return 0;
    }

    qsort(array, length, sizeof(*array), compare_int64);
    previous = array[0];

    for (size_t i = 1; i < length; ++i) {
        uint64_t delta;
        uint64_t contribution;
        uint64_t index;

        delta = (uint64_t)array[i] - (uint64_t)previous;

        if (i > UINT64_MAX) {
            return -1;
        }
        index = (uint64_t)i;

        if (delta != 0 && index > UINT64_MAX / delta) {
            return -1;
        }
        contribution = delta * index;

        if (prefix > UINT64_MAX - contribution) {
            return -1;
        }
        prefix += contribution;

        if (sum > UINT64_MAX - prefix) {
            return -1;
        }
        sum += prefix;

        previous = array[i];
    }

    *result = sum;
    return 0;
}

int main(void)
{
    size_t length;
    int64_t *array;
    uint64_t result;

    if (scanf("%zu", &length) != 1) {
        fputs("Invalid array length\n", stderr);
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(*array)) {
        fputs("Array is too large\n", stderr);
        return EXIT_FAILURE;
    }

    if (length == 0) {
        puts("0");
        return EXIT_SUCCESS;
    }

    array = malloc(length * sizeof(*array));
    if (array == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        /* Possible weaknesses found:
         * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
         */
        if (scanf("%" SCNd64, &array[i]) != 1) {
            fputs("Invalid array element\n", stderr);
            free(array);
            return EXIT_FAILURE;
        }
    }

    if (sum_absolute_differences(array, length, &result) != 0) {
        fputs("Result exceeds supported range\n", stderr);
        free(array);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    free(array);

    return EXIT_SUCCESS;
}