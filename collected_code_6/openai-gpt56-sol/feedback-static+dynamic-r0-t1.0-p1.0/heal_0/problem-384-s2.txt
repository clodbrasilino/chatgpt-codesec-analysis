#include <stdio.h>
#include <stdlib.h>

int frequency_of_smallest(const int *array, size_t length, size_t *frequency)
{
    if (array == NULL || frequency == NULL || length == 0U) {
        return -1;
    }

    int smallest = array[0];
    size_t count = 1U;

    for (size_t i = 1U; i < length; ++i) {
        if (array[i] < smallest) {
            smallest = array[i];
            count = 1U;
        } else if (array[i] == smallest) {
            ++count;
        }
    }

    *frequency = count;
    return 0;
}

int main(void)
{
    int values[] = {4, 2, 7, 2, 9, 2, 5};
    const size_t length = sizeof(values) / sizeof(values[0]);
    size_t frequency = 0U;

    if (frequency_of_smallest(values, length, &frequency) != 0) {
        fputs("Unable to determine the frequency.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", frequency) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}