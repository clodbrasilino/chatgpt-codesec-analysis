#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

bool count_rotations(const int *array, size_t length, size_t *rotations)
{
    size_t pivot = 0;
    bool pivot_found = false;

    if (rotations == NULL) {
        return false;
    }

    *rotations = 0;

    if (length == 0) {
        return true;
    }

    if (array == NULL) {
        return false;
    }

    for (size_t i = 1; i < length; ++i) {
        if (array[i] < array[i - 1]) {
            if (pivot_found) {
                return false;
            }

            pivot = i;
            pivot_found = true;
        }
    }

    if (pivot_found && array[length - 1] > array[0]) {
        return false;
    }

    *rotations = pivot;
    return true;
}

int main(void)
{
    const int array[] = {15, 18, 2, 3, 6, 12};
    const size_t length = sizeof(array) / sizeof(array[0]);
    size_t rotations = 0;

    if (!count_rotations(array, length, &rotations)) {
        fprintf(stderr, "Invalid rotated sorted array\n");
        return EXIT_FAILURE;
    }

    printf("%zu\n", rotations);
    return EXIT_SUCCESS;
}