#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

static int element_after_right_rotations(const int array[], size_t length,
                                         size_t index, size_t rotations,
                                         int *result)
{
    size_t normalized_rotations;
    size_t original_index;

    if (array == NULL || result == NULL || length == 0 || index >= length) {
        return 0;
    }

    normalized_rotations = rotations % length;
    original_index = (index + length - normalized_rotations) % length;
    *result = array[original_index];

    return 1;
}

int main(void)
{
    int array[] = {10, 20, 30, 40, 50};
    size_t length = sizeof(array) / sizeof(array[0]);
    size_t index;
    size_t rotations;
    int result;

    if (printf("Enter index and number of right rotations: ") < 0) {
        return EXIT_FAILURE;
    }

    if (scanf("%zu %zu", &index, &rotations) != 2) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!element_after_right_rotations(array, length, index, rotations, &result)) {
        fputs("Index out of range\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%d\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}