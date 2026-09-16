#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>

int find_max_difference(const int *array, size_t length, int64_t *result)
{
    int minimum;
    int maximum;

    if (array == NULL || result == NULL || length < 2U) {
        return 0;
    }

    minimum = array[0];
    maximum = array[0];

    for (size_t i = 1U; i < length; ++i) {
        if (array[i] < minimum) {
            minimum = array[i];
        }

        if (array[i] > maximum) {
            maximum = array[i];
        }
    }

    *result = (int64_t)maximum - (int64_t)minimum;
    return 1;
}

int main(void)
{
    const int values[] = {7, 1, 9, -4, 12, 3};
    const size_t length = sizeof(values) / sizeof(values[0]);
    int64_t maximum_difference;

    if (!find_max_difference(values, length, &maximum_difference)) {
        fputs("Unable to calculate the maximum difference.\n", stderr);
        return 1;
    }

    if (printf("Maximum difference: %" PRId64 "\n", maximum_difference) < 0) {
        return 1;
    }

    return 0;
}