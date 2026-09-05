#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void shell_sort(int *array, size_t size) {
    if (array == NULL || size < 2) {
        return;
    }

    size_t gap = size / 2;

    while (gap > 0) {
        for (size_t i = gap; i < size; i++) {
            int temp = array[i];
            size_t j = i;

            while (j >= gap && array[j - gap] > temp) {
                array[j] = array[j - gap];
                j -= gap;
            }

            array[j] = temp;
        }

        gap /= 2;
    }
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <integer1> <integer2> ...\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t size = argc - 1;
    int *array = (int *)malloc(size * sizeof(int));
    if (array == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < size; i++) {
        long val = strtol(argv[i + 1], NULL, 10);
        if (val < INT_MIN || val > INT_MAX) {
            fprintf(stderr, "Integer overflow or invalid input\n");
            free(array);
            return EXIT_FAILURE;
        }
        array[i] = (int)val;
    }

    shell_sort(array, size);

    for (size_t i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    free(array);
    array = NULL;

    return EXIT_SUCCESS;
}