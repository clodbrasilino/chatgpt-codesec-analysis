#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int compare_int64(const void *lhs, const void *rhs)
{
    const int64_t a = *(const int64_t *)lhs;
    const int64_t b = *(const int64_t *)rhs;

    return (a > b) - (a < b);
}

static int read_size(size_t *value)
{
    char buffer[128];
    char *end;
    uintmax_t parsed;

    if (value == NULL || fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return -1;
    }

    errno = 0;
    parsed = strtoumax(buffer, &end, 10);

    if (end == buffer || errno == ERANGE || parsed > SIZE_MAX) {
        return -1;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' || *end == '\n') {
        ++end;
    }

    if (*end != '\0') {
        return -1;
    }

    *value = (size_t)parsed;
    return 0;
}

static int read_int64(int64_t *value)
{
    char buffer[128];
    char *end;
    intmax_t parsed;

    if (value == NULL || fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return -1;
    }

    errno = 0;
    parsed = strtoimax(buffer, &end, 10);

    if (end == buffer || errno == ERANGE ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return -1;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' || *end == '\n') {
        ++end;
    }

    if (*end != '\0') {
        return -1;
    }

    *value = (int64_t)parsed;
    return 0;
}

static int sum_absolute_differences(int64_t *array, size_t length,
                                    uint64_t *result)
{
    uint64_t sum = 0;
    uint64_t positive_prefix = 0;
    uint64_t negative_prefix_magnitude = 0;

    if (array == NULL || result == NULL) {
        return -1;
    }

    qsort(array, length, sizeof(*array), compare_int64);

    for (size_t i = 0; i < length; ++i) {
        const uint64_t count = (uint64_t)i;
        uint64_t difference_sum;

        if ((size_t)count != i) {
            return -1;
        }

        if (array[i] >= 0) {
            const uint64_t value = (uint64_t)array[i];

            if (count != 0 && value > UINT64_MAX / count) {
                return -1;
            }

            difference_sum = value * count;

            if (difference_sum > UINT64_MAX - negative_prefix_magnitude) {
                return -1;
            }

            difference_sum += negative_prefix_magnitude;

            if (difference_sum < positive_prefix) {
                return -1;
            }

            difference_sum -= positive_prefix;

            if (positive_prefix > UINT64_MAX - value) {
                return -1;
            }

            positive_prefix += value;
        } else {
            const uint64_t magnitude =
                (uint64_t)(-(array[i] + INT64_C(1))) + UINT64_C(1);

            if (count != 0 && magnitude > UINT64_MAX / count) {
                return -1;
            }

            difference_sum = magnitude * count;

            if (difference_sum > UINT64_MAX - positive_prefix) {
                return -1;
            }

            difference_sum += positive_prefix;

            if (difference_sum < negative_prefix_magnitude) {
                return -1;
            }

            difference_sum -= negative_prefix_magnitude;

            if (negative_prefix_magnitude > UINT64_MAX - magnitude) {
                return -1;
            }

            negative_prefix_magnitude += magnitude;
        }

        if (sum > UINT64_MAX - difference_sum) {
            return -1;
        }

        sum += difference_sum;
    }

    *result = sum;
    return 0;
}

int main(void)
{
    size_t length;
    int64_t *array;
    uint64_t result;

    if (read_size(&length) != 0) {
        fputs("Invalid array length\n", stderr);
        return EXIT_FAILURE;
    }

    if (length == 0) {
        puts("0");
        return EXIT_SUCCESS;
    }

    if (length > SIZE_MAX / sizeof(*array)) {
        fputs("Array is too large\n", stderr);
        return EXIT_FAILURE;
    }

    array = malloc(length * sizeof(*array));
    if (array == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (read_int64(&array[i]) != 0) {
            fputs("Invalid array element\n", stderr);
            free(array);
            return EXIT_FAILURE;
        }
    }

    if (sum_absolute_differences(array, length, &result) != 0) {
        fputs("Result exceeds the supported range\n", stderr);
        free(array);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    free(array);

    return EXIT_SUCCESS;
}