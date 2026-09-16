#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>

static int max_contiguous_sum(const int64_t *array, size_t length, int64_t *result)
{
    if (array == NULL || result == NULL || length == 0U) {
        return -1;
    }

    int64_t current_sum = array[0];
    int64_t maximum_sum = array[0];

    for (size_t i = 1U; i < length; ++i) {
        if (current_sum > 0 && array[i] > INT64_MAX - current_sum) {
            return -1;
        }

        int64_t extended_sum = current_sum + array[i];
        current_sum = extended_sum > array[i] ? extended_sum : array[i];

        if (current_sum > maximum_sum) {
            maximum_sum = current_sum;
        }
    }

    *result = maximum_sum;
    return 0;
}

int main(void)
{
    int64_t array[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    size_t length = sizeof(array) / sizeof(array[0]);
    int64_t result = 0;

    errno = 0;

    if (max_contiguous_sum(array, length, &result) != 0) {
        if (fprintf(stderr, "Unable to calculate the maximum contiguous sum.\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("Largest contiguous subarray sum: %" PRId64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}