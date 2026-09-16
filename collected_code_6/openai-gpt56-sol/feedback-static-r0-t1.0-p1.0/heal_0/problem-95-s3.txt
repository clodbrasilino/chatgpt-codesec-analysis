#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>

static int minimum_subarray_length(const int *values, size_t count, int64_t target,
                                   size_t *result)
{
    size_t left = 0;
    size_t minimum = SIZE_MAX;
    int64_t sum = 0;

    if (values == NULL || result == NULL || count == 0 || target <= 0) {
        return -1;
    }

    for (size_t right = 0; right < count; ++right) {
        if (values[right] < 0 || sum > INT64_MAX - values[right]) {
            return -1;
        }

        sum += values[right];

        while (sum >= target) {
            size_t length = right - left + 1;

            if (length < minimum) {
                minimum = length;
            }

            sum -= values[left];
            ++left;
        }
    }

    *result = minimum == SIZE_MAX ? 0 : minimum;
    return 0;
}

int main(void)
{
    int values[] = {2, 3, 1, 2, 4, 3};
    size_t result = 0;
    size_t count = sizeof(values) / sizeof(values[0]);

    if (minimum_subarray_length(values, count, 7, &result) != 0) {
        fputs("Unable to calculate the minimum sublist length.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%zu\n", result);
    return EXIT_SUCCESS;
}