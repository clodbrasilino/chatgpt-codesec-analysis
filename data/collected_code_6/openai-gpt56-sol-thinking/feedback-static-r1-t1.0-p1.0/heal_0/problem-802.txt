#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool count_rotations(const int *array, size_t length, size_t *rotations)
{
    size_t pivot = 0;
    bool found_pivot = false;

    if (rotations == NULL || (array == NULL && length != 0)) {
        return false;
    }

    for (size_t i = 0; i + 1 < length; ++i) {
        if (array[i] > array[i + 1]) {
            if (found_pivot) {
                return false;
            }

            pivot = i + 1;
            found_pivot = true;
        }
    }

    if (found_pivot && array[length - 1] > array[0]) {
        return false;
    }

    *rotations = found_pivot ? pivot : 0;
    return true;
}

int main(void)
{
    size_t length;
    size_t rotations;
    int *array = NULL;

    if (scanf("%zu", &length) != 1) {
        fputs("Invalid array length\n", stderr);
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(*array)) {
        fputs("Array is too large\n", stderr);
        return EXIT_FAILURE;
    }

    if (length != 0) {
        array = malloc(length * sizeof(*array));
        if (array == NULL) {
            fputs("Memory allocation failed\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < length; ++i) {
        if (scanf("%d", &array[i]) != 1) {
            fputs("Invalid array element\n", stderr);
            free(array);
            return EXIT_FAILURE;
        }
    }

    if (!count_rotations(array, length, &rotations)) {
        fputs("The array cannot be sorted using rotations\n", stderr);
        free(array);
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", rotations) < 0) {
        free(array);
        return EXIT_FAILURE;
    }

    free(array);
    return EXIT_SUCCESS;
}