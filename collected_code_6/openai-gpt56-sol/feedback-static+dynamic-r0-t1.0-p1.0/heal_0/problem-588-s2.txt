#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>

int find_difference(const int *array, size_t length, int64_t *difference)
{
    if (array == NULL || difference == NULL || length == 0U) {
        return 0;
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

    *difference = (int64_t)largest - (int64_t)smallest;
    return 1;
}

int main(void)
{
    const int values[] = {12, -7, 25, 3, 18, -10};
    const size_t length = sizeof(values) / sizeof(values[0]);
    int64_t difference = 0;

    if (!find_difference(values, length, &difference)) {
        fputs("Unable to calculate the difference.\n", stderr);
        return 1;
    }

    printf("Difference: %" PRId64 "\n", difference);
    return 0;
}