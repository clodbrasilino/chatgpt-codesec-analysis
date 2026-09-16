#include <stdio.h>
#include <stdlib.h>

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
    size_t length;
    int target;

    if (scanf("%zu", &length) != 1) {
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(int)) {
        return EXIT_FAILURE;
    }

    int *array = NULL;

    if (length > 0) {
        array = malloc(length * sizeof(*array));
        if (array == NULL) {
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < length; ++i) {
        if (scanf("%d", &array[i]) != 1) {
            free(array);
            return EXIT_FAILURE;
        }
    }

    if (scanf("%d", &target) != 1) {
        free(array);
        return EXIT_FAILURE;
    }

    printf("%zu\n", find_frequency(array, length, target));

    free(array);
    return EXIT_SUCCESS;
}