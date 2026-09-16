#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

int largest_value_frequency(const int *array, size_t length, size_t *frequency)
{
    if (array == NULL || frequency == NULL || length == 0U) {
        return -1;
    }

    int largest = array[0];
    size_t count = 1U;

    for (size_t i = 1U; i < length; ++i) {
        if (array[i] > largest) {
            largest = array[i];
            count = 1U;
        } else if (array[i] == largest) {
            ++count;
        }
    }

    *frequency = count;
    return 0;
}

int main(void)
{
    const int values[] = {4, 9, 2, 9, 7, 9, 3};
    const size_t length = sizeof(values) / sizeof(values[0]);
    size_t frequency = 0U;

    if (largest_value_frequency(values, length, &frequency) != 0) {
        fputs("Unable to determine the frequency.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", frequency) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}