#include <limits.h>
#include <stddef.h>
#include <stdio.h>

static int max_contiguous_subarray_sum(const int array[], size_t length,
                                       long long *result)
{
    if (array == NULL || result == NULL || length == 0U) {
        return -1;
    }

    long long current_sum = array[0];
    long long maximum_sum = array[0];

    for (size_t i = 1U; i < length; ++i) {
        const long long value = array[i];

        if (current_sum > 0) {
            if (value > 0 && current_sum > LLONG_MAX - value) {
                return -1;
            }

            current_sum += value;
        } else {
            current_sum = value;
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
    const int array[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    const size_t length = sizeof array / sizeof array[0];
    long long result;

    if (max_contiguous_subarray_sum(array, length, &result) != 0) {
        fputs("Unable to calculate the maximum subarray sum.\n", stderr);
        return 1;
    }

    if (printf("%lld\n", result) < 0) {
        return 1;
    }

    return 0;
}