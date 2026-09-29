#include <stdio.h>
#include <stddef.h>

size_t max_sum_subarray_length(const long long array[], size_t length)
{
    if (array == NULL || length == 0U) {
        return 0U;
    }

    long long current_sum = array[0];
    long long maximum_sum = array[0];
    size_t current_start = 0U;
    size_t maximum_start = 0U;
    size_t maximum_length = 1U;

    for (size_t i = 1U; i < length; ++i) {
        if (current_sum < 0) {
            current_sum = array[i];
            current_start = i;
        } else {
            current_sum += array[i];
        }

        size_t current_length = i - current_start + 1U;

        if (current_sum > maximum_sum ||
            (current_sum == maximum_sum &&
             (current_length > maximum_length ||
              (current_length == maximum_length &&
               current_start < maximum_start)))) {
            maximum_sum = current_sum;
            maximum_start = current_start;
            maximum_length = current_length;
        }
    }

    return maximum_length;
}

int main(void)
{
    long long array[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    size_t length = sizeof(array) / sizeof(array[0]);
    size_t result = max_sum_subarray_length(array, length);

    if (result == 0U) {
        return 1;
    }

    if (printf("%zu\n", result) < 0) {
        return 1;
    }

    return 0;
}