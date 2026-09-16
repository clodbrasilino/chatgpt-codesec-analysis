#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

bool count_rotations(const int *array, size_t length, size_t *rotations)
{
    size_t drop_index = 0;
    size_t drop_count = 0;

    if (array == NULL || rotations == NULL || length == 0) {
        return false;
    }

    for (size_t i = 1; i < length; ++i) {
        if (array[i] < array[i - 1]) {
            drop_index = i;
            ++drop_count;

            if (drop_count > 1) {
                return false;
            }
        }
    }

    if (drop_count == 0) {
        *rotations = 0;
        return true;
    }

    if (array[length - 1] > array[0]) {
        return false;
    }

    *rotations = drop_index;
    return true;
}

int main(void)
{
    int *array = NULL;
    size_t length = 0;
    size_t rotations = 0;

    if (scanf("%zu", &length) != 1 || length == 0 ||
        length > SIZE_MAX / sizeof(*array)) {
        fprintf(stderr, "Invalid array length\n");
        return EXIT_FAILURE;
    }

    array = malloc(length * sizeof(*array));
    if (array == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (scanf("%d", &array[i]) != 1) {
            fprintf(stderr, "Invalid array element\n");
            free(array);
            return EXIT_FAILURE;
        }
    }

    if (!count_rotations(array, length, &rotations)) {
        fprintf(stderr, "Array is not a rotation of a sorted array\n");
        free(array);
        return EXIT_FAILURE;
    }

    printf("%zu\n", rotations);

    free(array);
    return EXIT_SUCCESS;
}