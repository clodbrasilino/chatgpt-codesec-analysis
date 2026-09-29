#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int element_after_rotations(const int *array, size_t length,
                                   size_t index, int64_t rotations,
                                   int *result)
{
    int64_t normalized;
    size_t original_index;

    if (array == NULL || result == NULL || length == 0 || index >= length) {
        return -1;
    }

    normalized = rotations % (int64_t)length;
    if (normalized < 0) {
        normalized += (int64_t)length;
    }

    original_index = (index + length - (size_t)normalized) % length;
    *result = array[original_index];

    return 0;
}

int main(void)
{
    size_t length;
    size_t index;
    int64_t rotations;
    int *array = NULL;
    int result;
    size_t i;

    if (scanf("%zu", &length) != 1 || length == 0 ||
        length > SIZE_MAX / sizeof(*array)) {
        return EXIT_FAILURE;
    }

    array = malloc(length * sizeof(*array));
    if (array == NULL) {
        return EXIT_FAILURE;
    }

    for (i = 0; i < length; ++i) {
        if (scanf("%d", &array[i]) != 1) {
            free(array);
            return EXIT_FAILURE;
        }
    }

    if (scanf("%zu%lld", &index, (long long *)&rotations) != 2 ||
        element_after_rotations(array, length, index, rotations, &result) != 0) {
        free(array);
        return EXIT_FAILURE;
    }

    printf("%d\n", result);
    free(array);

    return EXIT_SUCCESS;
}