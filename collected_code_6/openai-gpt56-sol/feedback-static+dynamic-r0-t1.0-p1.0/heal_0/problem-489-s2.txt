#include <stdio.h>
#include <stdlib.h>

int largest_value_frequency(const int array[], size_t length, size_t *frequency)
{
    int largest;
    size_t count = 1;

    if (array == NULL || frequency == NULL || length == 0) {
        return 0;
    }

    largest = array[0];

    for (size_t i = 1; i < length; ++i) {
        if (array[i] > largest) {
            largest = array[i];
            count = 1;
        } else if (array[i] == largest) {
            ++count;
        }
    }

    *frequency = count;
    return 1;
}

int main(void)
{
    int array[] = {4, 9, 2, 9, 7, 9, 3};
    const size_t length = sizeof(array) / sizeof(array[0]);
    size_t frequency = 0;

    if (!largest_value_frequency(array, length, &frequency)) {
        fputs("Unable to determine the frequency.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%zu\n", frequency);
    return EXIT_SUCCESS;
}