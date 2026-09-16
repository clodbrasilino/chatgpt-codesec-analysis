#include <stdio.h>
#include <stdlib.h>

void shell_sort(int *array, size_t size) {
    if (array == NULL || size < 2) {
        return;
    }

    for (size_t gap = size / 2; gap > 0; gap /= 2) {
        for (size_t i = gap; i < size; i++) {
            int temp = array[i];
            size_t j = i;
            while (j >= gap && array[j - gap] > temp) {
                array[j] = array[j - gap];
                j -= gap;
            }
            array[j] = temp;
        }
    }
}

int main(void) {
    size_t size = 0;
    int *array = NULL;

    if (scanf("%zu", &size) != 1) {
        return EXIT_FAILURE;
    }

    if (size == 0) {
        return EXIT_SUCCESS;
    }

    array = (int *)malloc(size * sizeof(int));
    if (array == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < size; i++) {
        if (scanf("%d", &array[i]) != 1) {
            free(array);
            return EXIT_FAILURE;
        }
    }

    shell_sort(array, size);

    for (size_t i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    free(array);

    return EXIT_SUCCESS;
}