#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>

int find_max_difference(const int *array, size_t length, int64_t *result)
{
    if (array == NULL || result == NULL || length < 2U) {
        return -1;
    }

    int minimum = array[0];
    int maximum = array[0];

    for (size_t i = 1U; i < length; ++i) {
        if (array[i] < minimum) {
            minimum = array[i];
        }
        if (array[i] > maximum) {
            maximum = array[i];
        }
    }

    *result = (int64_t)maximum - (int64_t)minimum;
    return 0;
}

int main(void)
{
    const int values[] = {7, 1, 9, -3, 12, 4};
    const size_t length = sizeof(values) / sizeof(values[0]);
    int64_t maximum_difference = 0;

    if (find_max_difference(values, length, &maximum_difference) != 0) {
        (void)fprintf(stderr, "Unable to calculate the maximum difference.\n");
        return 1;
    }

    if (printf("Maximum difference: %" PRId64 "\n", maximum_difference) < 0) {
        return 1;
    }

    return 0;
}