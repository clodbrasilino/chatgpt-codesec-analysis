#include <stdio.h>
#include <stdlib.h>

static void shell_sort(int array[], size_t length)
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
    size_t length = 0;

    if (scanf("%zu", &length) != 1 || length == 0 ||
        length > SIZE_MAX / sizeof(int)) {
        return EXIT_FAILURE;
    }

    int *array = malloc(length * sizeof(*array));
    if (array == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (scanf("%d", &array[i]) != 1) {
            free(array);
            return EXIT_FAILURE;
        }
    }

    shell_sort(array, length);

    for (size_t i = 0; i < length; ++i) {
        if (printf("%d%s", array[i], i + 1 == length ? "\n" : " ") < 0) {
            free(array);
            return EXIT_FAILURE;
        }
    }

    free(array);
    return EXIT_SUCCESS;
}