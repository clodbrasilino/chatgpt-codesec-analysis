#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>

static int compare_ints(const void *a, const void *b)
{
    const int x = *(const int *)a;
    const int y = *(const int *)b;

    return (x > y) - (x < y);
}

static int frequency_difference(const int *array, size_t length, size_t *difference)
{
    int *copy;
    size_t current_frequency = 1;
    size_t minimum_frequency;
    size_t maximum_frequency;
    size_t i;

    if (array == NULL || difference == NULL || length == 0 ||
        length > SIZE_MAX / sizeof(*copy)) {
        return -1;
    }

    copy = malloc(length * sizeof(*copy));
    if (copy == NULL) {
        return -1;
    }

    for (i = 0; i < length; ++i) {
        copy[i] = array[i];
    }

    qsort(copy, length, sizeof(*copy), compare_ints);

    minimum_frequency = length;
    maximum_frequency = 0;

    for (i = 1; i <= length; ++i) {
        if (i < length && copy[i] == copy[i - 1]) {
            ++current_frequency;
        } else {
            if (current_frequency < minimum_frequency) {
                minimum_frequency = current_frequency;
            }
            if (current_frequency > maximum_frequency) {
                maximum_frequency = current_frequency;
            }
            current_frequency = 1;
        }
    }

    *difference = maximum_frequency - minimum_frequency;
    free(copy);
    return 0;
}

int main(void)
{
    int array[] = {1, 2, 2, 3, 3, 3, 4, 4};
    const size_t length = sizeof(array) / sizeof(array[0]);
    size_t difference;

    if (frequency_difference(array, length, &difference) != 0) {
        fputs("Unable to calculate the frequency difference.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%zu\n", difference);
    return EXIT_SUCCESS;
}