#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>

static int max_increasing_subsequence_sum(const int64_t *array,
                                          size_t length,
                                          int64_t *result)
{
    int64_t *sums;
    int64_t maximum;

    if (array == NULL || result == NULL || length == 0U) {
        return -1;
    }

    if (length > SIZE_MAX / sizeof(*sums)) {
        return -1;
    }

    sums = malloc(length * sizeof(*sums));
    if (sums == NULL) {
        return -1;
    }

    maximum = array[0];

    for (size_t i = 0U; i < length; ++i) {
        sums[i] = array[i];

        for (size_t j = 0U; j < i; ++j) {
            if (array[j] < array[i]) {
                if ((array[i] > 0 && sums[j] > INT64_MAX - array[i]) ||
                    (array[i] < 0 && sums[j] < INT64_MIN - array[i])) {
                    free(sums);
                    return -1;
                }

                int64_t candidate = sums[j] + array[i];
                if (candidate > sums[i]) {
                    sums[i] = candidate;
                }
            }
        }

        if (sums[i] > maximum) {
            maximum = sums[i];
        }
    }

    free(sums);
    *result = maximum;
    return 0;
}

int main(void)
{
    size_t length;
    int64_t *array;
    int64_t result;

    if (scanf("%zu", &length) != 1 || length == 0U) {
        fprintf(stderr, "Invalid array length\n");
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(*array)) {
        fprintf(stderr, "Array is too large\n");
        return EXIT_FAILURE;
    }

    array = malloc(length * sizeof(*array));
    if (array == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < length; ++i) {
        if (scanf("%" SCNd64, &array[i]) != 1) {
            fprintf(stderr, "Invalid array element\n");
            free(array);
            return EXIT_FAILURE;
        }
    }

    if (max_increasing_subsequence_sum(array, length, &result) != 0) {
        fprintf(stderr, "Unable to compute the result\n");
        free(array);
        return EXIT_FAILURE;
    }

    printf("%" PRId64 "\n", result);
    free(array);
    return EXIT_SUCCESS;
}