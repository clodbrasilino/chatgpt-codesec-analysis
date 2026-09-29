#include <stdio.h>
#include <stdlib.h>

int largest_value_frequency(const int *array, size_t length, size_t *frequency)
{
    int largest;
    size_t count = 0;

    if (array == NULL || frequency == NULL || length == 0) {
        return 0;
    }

    largest = array[0];

    for (size_t i = 1; i < length; ++i) {
        if (array[i] > largest) {
            largest = array[i];
        }
    }

    for (size_t i = 0; i < length; ++i) {
        if (array[i] == largest) {
            ++count;
        }
    }

    *frequency = count;
    return 1;
}

int main(void)
{
    int values[] = {4, 8, 2, 8, 5, 8, 1};
    size_t length = sizeof(values) / sizeof(values[0]);
    size_t frequency;

    if (!largest_value_frequency(values, length, &frequency)) {
        fputs("Unable to determine the frequency.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", frequency) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}