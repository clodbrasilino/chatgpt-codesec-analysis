#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

static int sum_odd_length_subarrays(const int *array, size_t length, int64_t *result)
{
    if (array == NULL || result == NULL) {
        return -1;
    }

    int64_t sum = 0;

    for (size_t i = 0; i < length; ++i) {
        size_t total = (i + 1U) * (length - i);
        size_t occurrences = (total + 1U) / 2U;
        sum += (int64_t)array[i] * (int64_t)occurrences;
    }

    *result = sum;
    return 0;
}

int main(void)
{
    size_t length;

    if (scanf("%zu", &length) != 1 || length == 0U) {
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(int)) {
        return EXIT_FAILURE;
    }

    int *array = malloc(length * sizeof(*array));
    if (array == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (scanf("%d", &array[i]) != 1) {
            free(array);
            return EXIT_FAILURE;
        }
    }

    int64_t result;
    if (sum_odd_length_subarrays(array, length, &result) != 0) {
        free(array);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", result) < 0) {
        free(array);
        return EXIT_FAILURE;
    }

    free(array);
    return EXIT_SUCCESS;
}