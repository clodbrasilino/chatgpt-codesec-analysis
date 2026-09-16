#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static size_t rotation_count(const int *array, size_t length)
{
    size_t low = 0U;
    size_t high = length - 1U;

    while (low < high) {
        size_t middle;

        if (array[low] < array[high]) {
            return low;
        }

        middle = low + (high - low) / 2U;

        if (array[middle] > array[high]) {
            low = middle + 1U;
        } else if (array[middle] < array[high]) {
            high = middle;
        } else {
            --high;
        }
    }

    return low;
}

int main(void)
{
    int *array = NULL;
    size_t length;
    size_t i;
    size_t rotations;
    int result;

    result = scanf("%zu", &length);
    if (result != 1 || length == 0U || length > SIZE_MAX / sizeof(*array)) {
        return EXIT_FAILURE;
    }

    array = malloc(length * sizeof(*array));
    if (array == NULL) {
        return EXIT_FAILURE;
    }

    for (i = 0U; i < length; ++i) {
        if (scanf("%d", &array[i]) != 1) {
            free(array);
            return EXIT_FAILURE;
        }
    }

    rotations = rotation_count(array, length);

    if (printf("%zu\n", rotations) < 0) {
        free(array);
        return EXIT_FAILURE;
    }

    free(array);
    return EXIT_SUCCESS;
}