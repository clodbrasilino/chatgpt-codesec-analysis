#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int find_max_sum_subarray_length(const int *array, size_t size, size_t *length)
{
    if (array == NULL || length == NULL || size == 0U) {
        return -1;
    }

    int64_t current_sum = array[0];
    int64_t maximum_sum = array[0];
    size_t current_start = 0U;
    size_t best_start = 0U;
    size_t best_end = 0U;

    for (size_t i = 1U; i < size; ++i) {
        int64_t value = array[i];

        if (current_sum < 0) {
            current_sum = value;
            current_start = i;
        } else {
            current_sum += value;
        }

        size_t current_length = i - current_start + 1U;
        size_t best_length = best_end - best_start + 1U;

        if (current_sum > maximum_sum ||
            (current_sum == maximum_sum && current_length > best_length)) {
            maximum_sum = current_sum;
            best_start = current_start;
            best_end = i;
        }
    }

    *length = best_end - best_start + 1U;
    return 0;
}

int main(void)
{
    int array[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    size_t size = sizeof(array) / sizeof(array[0]);
    size_t length = 0U;

    if (find_max_sum_subarray_length(array, size, &length) != 0) {
        fputs("Unable to determine the subarray length.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", length) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}