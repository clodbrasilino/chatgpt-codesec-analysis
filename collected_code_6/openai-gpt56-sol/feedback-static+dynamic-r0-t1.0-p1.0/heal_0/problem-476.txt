#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <limits.h>

static bool sum_of_min_and_max(const int values[], size_t length, long long *result)
{
    if (values == NULL || result == NULL || length == 0U) {
        return false;
    }

    int smallest = values[0];
    int largest = values[0];

    for (size_t i = 1U; i < length; ++i) {
        if (values[i] < smallest) {
            smallest = values[i];
        }

        if (values[i] > largest) {
            largest = values[i];
        }
    }

    *result = (long long)smallest + (long long)largest;
    return true;
}

int main(void)
{
    const int values[] = {12, -4, 7, 25, 3, 0};
    const size_t length = sizeof(values) / sizeof(values[0]);
    long long result = 0;

    if (!sum_of_min_and_max(values, length, &result)) {
        fputs("Unable to calculate the sum.\n", stderr);
        return 1;
    }

    if (printf("%lld\n", result) < 0) {
        return 1;
    }

    return 0;
}