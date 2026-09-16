#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int sequential_search(const int *array, size_t length, int target, size_t *index)
{
    if (array == NULL || index == NULL) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        if (array[i] == target) {
            *index = i;
            return 1;
        }
    }

    return 0;
}

int main(void)
{
    size_t length = 0;
    int target = 0;

    if (scanf("%zu", &length) != 1) {
        fprintf(stderr, "Invalid array length.\n");
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(int)) {
        fprintf(stderr, "Array length is too large.\n");
        return EXIT_FAILURE;
    }

    int *array = NULL;

    if (length > 0) {
        array = malloc(length * sizeof(*array));
        if (array == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < length; ++i) {
        if (scanf("%d", &array[i]) != 1) {
            fprintf(stderr, "Invalid array element.\n");
            free(array);
            return EXIT_FAILURE;
        }
    }

    if (scanf("%d", &target) != 1) {
        fprintf(stderr, "Invalid search target.\n");
        free(array);
        return EXIT_FAILURE;
    }

    size_t index = 0;

    if (sequential_search(array, length, target, &index)) {
        printf("Element found at index %zu\n", index);
    } else {
        printf("Element not found\n");
    }

    free(array);
    return EXIT_SUCCESS;
}