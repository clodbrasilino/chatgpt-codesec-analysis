#include <stdio.h>
#include <stdlib.h>

static int find_rotation_count(const int *array, size_t length, size_t *count)
{
    size_t low;
    size_t high;

    if (array == NULL || count == NULL || length == 0U) {
        return 0;
    }

    low = 0U;
    high = length - 1U;

    while (low < high) {
        size_t middle = low + (high - low) / 2U;

        if (array[middle] < array[high]) {
            high = middle;
        } else if (array[middle] > array[high]) {
            low = middle + 1U;
        } else {
            --high;
        }
    }

    *count = low;
    return 1;
}

int main(void)
{
    int *array = NULL;
    size_t length;
    size_t rotation_count;
    size_t index;

    if (scanf("%zu", &length) != 1 || length == 0U) {
        fputs("Invalid array length\n", stderr);
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(*array)) {
        fputs("Array is too large\n", stderr);
        return EXIT_FAILURE;
    }

    array = malloc(length * sizeof(*array));
    if (array == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (index = 0U; index < length; ++index) {
        if (scanf("%d", &array[index]) != 1) {
            fputs("Invalid array element\n", stderr);
            free(array);
            return EXIT_FAILURE;
        }
    }

    if (!find_rotation_count(array, length, &rotation_count)) {
        fputs("Unable to determine rotation count\n", stderr);
        free(array);
        return EXIT_FAILURE;
    }

    printf("%zu\n", rotation_count);
    free(array);

    return EXIT_SUCCESS;
}