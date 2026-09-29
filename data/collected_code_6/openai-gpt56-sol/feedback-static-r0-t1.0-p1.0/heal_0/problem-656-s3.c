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

static int minimum_absolute_difference_sum(
    int64_t *first,
    int64_t *second,
    size_t length,
    uint64_t *result)
{
    uint64_t sum = 0;

    if (first == NULL || second == NULL || result == NULL) {
        return -1;
    }

    qsort(first, length, sizeof(*first), compare_int64);
    qsort(second, length, sizeof(*second), compare_int64);

    for (size_t i = 0; i < length; ++i) {
        uint64_t difference;

        if (first[i] >= second[i]) {
            difference = (uint64_t)first[i] - (uint64_t)second[i];
        } else {
            difference = (uint64_t)second[i] - (uint64_t)first[i];
        }

        if (UINT64_MAX - sum < difference) {
            return -1;
        }

        sum += difference;
    }

    *result = sum;
    return 0;
}

static int read_array(int64_t *array, size_t length)
{
    for (size_t i = 0; i < length; ++i) {
        if (scanf("%" SCNd64, &array[i]) != 1) {
            return -1;
        }
    }

    return 0;
}

int main(void)
{
    size_t length;
    int64_t *first = NULL;
    int64_t *second = NULL;
    uint64_t result;
    int status = EXIT_FAILURE;

    errno = 0;
    if (scanf("%zu", &length) != 1 || length == 0) {
        fputs("Invalid array length\n", stderr);
        goto cleanup;
    }

    if (length > SIZE_MAX / sizeof(*first)) {
        fputs("Array length is too large\n", stderr);
        goto cleanup;
    }

    first = malloc(length * sizeof(*first));
    second = malloc(length * sizeof(*second));

    if (first == NULL || second == NULL) {
        fputs("Memory allocation failed\n", stderr);
        goto cleanup;
    }

    if (read_array(first, length) != 0 ||
        read_array(second, length) != 0) {
        fputs("Invalid array input\n", stderr);
        goto cleanup;
    }

    if (minimum_absolute_difference_sum(first, second, length, &result) != 0) {
        fputs("Unable to compute result\n", stderr);
        goto cleanup;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        fputs("Output error\n", stderr);
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(second);
    free(first);
    return status;
}