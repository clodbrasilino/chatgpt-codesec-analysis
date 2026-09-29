#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>

static int max_subarray_sum(const int64_t *array, size_t length, int64_t *result)
{
    if (array == NULL || result == NULL || length == 0U) {
        return -1;
    }

    int64_t current_sum = array[0];
    int64_t maximum_sum = array[0];

    for (size_t i = 1U; i < length; ++i) {
        if (current_sum < 0) {
            current_sum = array[i];
        } else {
            if (array[i] > 0 && current_sum > INT64_MAX - array[i]) {
                return -1;
            }
            current_sum += array[i];
        }

        if (current_sum > maximum_sum) {
            maximum_sum = current_sum;
        }
    }

    *result = maximum_sum;
    return 0;
}

int main(void)
{
    const int64_t array[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    const size_t length = sizeof(array) / sizeof(array[0]);
    int64_t result = 0;

    if (max_subarray_sum(array, length, &result) != 0) {
        fputs("Unable to calculate the maximum subarray sum.\n", stderr);
        return 1;
    }

    if (printf("Largest contiguous subarray sum: %" PRId64 "\n", result) < 0) {
        return 1;
    }

    return 0;
}