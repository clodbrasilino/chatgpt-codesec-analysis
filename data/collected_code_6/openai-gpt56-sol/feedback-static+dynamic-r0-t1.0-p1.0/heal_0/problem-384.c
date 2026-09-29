#include <stdio.h>
#include <stdlib.h>

static int smallest_value_frequency(const int *array, size_t length, size_t *frequency)
{
    int smallest;
    size_t count = 1;

    if (array == NULL || frequency == NULL || length == 0) {
        return -1;
    }

    smallest = array[0];

    for (size_t i = 1; i < length; ++i) {
        if (array[i] < smallest) {
            smallest = array[i];
            count = 1;
        } else if (array[i] == smallest) {
            ++count;
        }
    }

    *frequency = count;
    return 0;
}

int main(void)
{
    int values[] = {4, 2, 7, 2, -1, 5, -1, -1};
    const size_t length = sizeof(values) / sizeof(values[0]);
    size_t frequency = 0;

    if (smallest_value_frequency(values, length, &frequency) != 0) {
        fputs("Unable to determine the frequency.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", frequency) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}