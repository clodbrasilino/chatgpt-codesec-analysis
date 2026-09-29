#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <limits.h>

static bool find_difference(const int array[], size_t length, long long *difference)
{
    if (array == NULL || difference == NULL || length == 0U) {
        return false;
    }

    int smallest = array[0];
    int largest = array[0];

    for (size_t i = 1U; i < length; ++i) {
        if (array[i] < smallest) {
            smallest = array[i];
        }

        if (array[i] > largest) {
            largest = array[i];
        }
    }

    *difference = (long long)largest - (long long)smallest;
    return true;
}

int main(void)
{
    const int values[] = {12, -7, 25, 3, 9, INT_MIN, INT_MAX};
    const size_t length = sizeof(values) / sizeof(values[0]);
    long long difference = 0;

    if (!find_difference(values, length, &difference)) {
        (void)fprintf(stderr, "Unable to calculate the difference.\n");
        return 1;
    }

    if (printf("%lld\n", difference) < 0) {
        return 1;
    }

    return 0;
}