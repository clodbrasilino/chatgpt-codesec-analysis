#include <stdio.h>
#include <stdlib.h>

static void shell_sort(int *array, size_t length)
{
    for (size_t gap = length / 2; gap > 0; gap /= 2) {
        for (size_t i = gap; i < length; ++i) {
            int value = array[i];
            size_t j = i;

            while (j >= gap && array[j - gap] > value) {
                array[j] = array[j - gap];
                j -= gap;
            }

            array[j] = value;
        }
    }
}

int main(void)
{
    size_t length;

    if (scanf("%zu", &length) != 1) {
        fprintf(stderr, "Failed to read array length.\n");
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
            fprintf(stderr, "Failed to read array element.\n");
            free(array);
            return EXIT_FAILURE;
        }
    }

    shell_sort(array, length);

    for (size_t i = 0; i < length; ++i) {
        if (printf("%s%d", i == 0 ? "" : " ", array[i]) < 0) {
            free(array);
            return EXIT_FAILURE;
        }
    }

    if (putchar('\n') == EOF) {
        free(array);
        return EXIT_FAILURE;
    }

    free(array);
    return EXIT_SUCCESS;
}