#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>

static int max_sum_increasing_subsequence(const int *array, size_t length,
                                          int64_t *result)
{
    int64_t *sums = NULL;
    int64_t maximum;

    if (array == NULL || result == NULL || length == 0 ||
        length > SIZE_MAX / sizeof(*sums)) {
        return -1;
    }

    sums = malloc(length * sizeof(*sums));
    if (sums == NULL) {
        return -1;
    }

    maximum = array[0];

    for (size_t i = 0; i < length; ++i) {
        sums[i] = array[i];

        for (size_t j = 0; j < i; ++j) {
            if (array[j] < array[i]) {
                int64_t candidate = sums[j] + (int64_t)array[i];

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
    int array[] = {1, 101, 2, 3, 100, 4, 5};
    const size_t length = sizeof(array) / sizeof(array[0]);
    int64_t result;

    if (max_sum_increasing_subsequence(array, length, &result) != 0) {
        fputs("Unable to calculate the result.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("Maximum sum: %" PRId64 "\n", result);
    return EXIT_SUCCESS;
}