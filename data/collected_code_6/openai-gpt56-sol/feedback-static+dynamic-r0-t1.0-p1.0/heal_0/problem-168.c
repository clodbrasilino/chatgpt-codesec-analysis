#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

static size_t find_frequency(const int *array, size_t length, int target)
{
    size_t frequency = 0;

    if (array == NULL && length != 0) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        if (array[i] == target) {
            ++frequency;
        }
    }

    return frequency;
}

int main(void)
{
    size_t length = 0;
    int target = 0;

    if (scanf("%zu", &length) != 1) {
        fputs("Invalid array length.\n", stderr);
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(int)) {
        fputs("Array length is too large.\n", stderr);
        return EXIT_FAILURE;
    }

    int *array = NULL;

    if (length > 0) {
        array = malloc(length * sizeof(*array));
        if (array == NULL) {
            fputs("Memory allocation failed.\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < length; ++i) {
        if (scanf("%d", &array[i]) != 1) {
            fputs("Invalid array element.\n", stderr);
            free(array);
            return EXIT_FAILURE;
        }
    }

    if (scanf("%d", &target) != 1) {
        fputs("Invalid target number.\n", stderr);
        free(array);
        return EXIT_FAILURE;
    }

    printf("%zu\n", find_frequency(array, length, target));

    free(array);
    return EXIT_SUCCESS;
}