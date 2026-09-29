#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool add_int64(int64_t a, int64_t b, int64_t *result)
{
    if ((b > 0 && a > INT64_MAX - b) ||
        (b < 0 && a < INT64_MIN - b)) {
        return false;
    }

    *result = a + b;
    return true;
}

static bool subtract_int64(int64_t a, int64_t b, int64_t *result)
{
    if ((b > 0 && a < INT64_MIN + b) ||
        (b < 0 && a > INT64_MAX + b)) {
        return false;
    }

    *result = a - b;
    return true;
}

bool maximum_sum_bitonic_subsequence(const int *array, size_t length,
                                     int64_t *result)
{
    int64_t *increasing;
    int64_t *decreasing;
    int64_t maximum;

    if (array == NULL || result == NULL || length == 0 ||
        length > SIZE_MAX / sizeof(*increasing)) {
        return false;
    }

    increasing = malloc(length * sizeof(*increasing));
    if (increasing == NULL) {
        return false;
    }

    decreasing = malloc(length * sizeof(*decreasing));
    if (decreasing == NULL) {
        free(increasing);
        return false;
    }

    for (size_t i = 0; i < length; ++i) {
        increasing[i] = array[i];

        for (size_t j = 0; j < i; ++j) {
            if (array[j] < array[i]) {
                int64_t candidate;

                if (!add_int64(increasing[j], array[i], &candidate)) {
                    free(decreasing);
                    free(increasing);
                    return false;
                }

                if (candidate > increasing[i]) {
                    increasing[i] = candidate;
                }
            }
        }
    }

    for (size_t i = length; i-- > 0;) {
        decreasing[i] = array[i];

        for (size_t j = i + 1; j < length; ++j) {
            if (array[j] < array[i]) {
                int64_t candidate;

                if (!add_int64(decreasing[j], array[i], &candidate)) {
                    free(decreasing);
                    free(increasing);
                    return false;
                }

                if (candidate > decreasing[i]) {
                    decreasing[i] = candidate;
                }
            }
        }
    }

    maximum = INT64_MIN;

    for (size_t i = 0; i < length; ++i) {
        int64_t combined;
        int64_t candidate;

        if (!add_int64(increasing[i], decreasing[i], &combined) ||
            !subtract_int64(combined, array[i], &candidate)) {
            free(decreasing);
            free(increasing);
            return false;
        }

        if (candidate > maximum) {
            maximum = candidate;
        }
    }

    free(decreasing);
    free(increasing);
    *result = maximum;
    return true;
}

int main(void)
{
    size_t length;
    int *array;
    int64_t result;

    if (scanf("%zu", &length) != 1 || length == 0 ||
        length > SIZE_MAX / sizeof(*array)) {
        fprintf(stderr, "Invalid array length\n");
        return EXIT_FAILURE;
    }

    array = malloc(length * sizeof(*array));
    if (array == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (scanf("%d", &array[i]) != 1) {
            fprintf(stderr, "Invalid array element\n");
            free(array);
            return EXIT_FAILURE;
        }
    }

    if (!maximum_sum_bitonic_subsequence(array, length, &result)) {
        fprintf(stderr, "Unable to calculate the result\n");
        free(array);
        return EXIT_FAILURE;
    }

    printf("%" PRId64 "\n", result);
    free(array);
    return EXIT_SUCCESS;
}