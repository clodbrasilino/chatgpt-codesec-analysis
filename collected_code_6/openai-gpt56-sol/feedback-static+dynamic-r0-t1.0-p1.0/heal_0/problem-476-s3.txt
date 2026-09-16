#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>

static bool sum_of_extremes(const int64_t array[], size_t length, int64_t *result)
{
    if (array == NULL || result == NULL || length == 0U) {
        return false;
    }

    int64_t smallest = array[0];
    int64_t largest = array[0];

    for (size_t i = 1U; i < length; ++i) {
        if (array[i] < smallest) {
            smallest = array[i];
        }

        if (array[i] > largest) {
            largest = array[i];
        }
    }

    if ((largest > 0 && smallest > INT64_MAX - largest) ||
        (largest < 0 && smallest < INT64_MIN - largest)) {
        return false;
    }

    *result = smallest + largest;
    return true;
}

int main(void)
{
    const int64_t values[] = {12, -4, 7, 25, 3, -10};
    const size_t length = sizeof(values) / sizeof(values[0]);
    int64_t result = 0;

    if (!sum_of_extremes(values, length, &result)) {
        fputs("Unable to calculate the sum.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}