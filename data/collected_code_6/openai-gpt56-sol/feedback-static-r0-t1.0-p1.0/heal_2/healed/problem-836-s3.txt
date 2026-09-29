#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>

static int add_overflows_int64(int64_t a, int64_t b)
{
    return (b > 0 && a > INT64_MAX - b) ||
           (b < 0 && a < INT64_MIN - b);
}

static size_t max_sum_subarray_length(const int64_t *array, size_t length)
{
    if (array == NULL || length == 0) {
        return 0;
    }

    int64_t current_sum = array[0];
    int64_t maximum_sum = array[0];
    size_t current_start = 0;
    size_t best_length = 1;

    for (size_t i = 1; i < length; ++i) {
        if (current_sum < 0 || add_overflows_int64(current_sum, array[i])) {
            current_sum = array[i];
            current_start = i;
        } else {
            current_sum += array[i];
        }

        size_t current_length = i - current_start + 1;

        if (current_sum > maximum_sum ||
            (current_sum == maximum_sum && current_length > best_length)) {
            maximum_sum = current_sum;
            best_length = current_length;
        }
    }

    return best_length;
}

int main(void)
{
    size_t length;

    if (scanf("%zu", &length) != 1 ||
        length == 0 ||
        length > SIZE_MAX / sizeof(int64_t)) {
        return EXIT_FAILURE;
    }

    int64_t *array = malloc(length * sizeof(*array));
    if (array == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (scanf("%" SCNd64, &array[i]) != 1) {
            free(array);
            return EXIT_FAILURE;
        }
    }

    size_t result = max_sum_subarray_length(array, length);

    if (printf("%zu\n", result) < 0) {
        free(array);
        return EXIT_FAILURE;
    }

    free(array);
    return EXIT_SUCCESS;
}