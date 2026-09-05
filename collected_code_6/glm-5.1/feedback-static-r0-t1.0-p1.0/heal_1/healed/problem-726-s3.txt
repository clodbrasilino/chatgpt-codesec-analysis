#include <stdio.h>
#include <stdlib.h>

int multiply_adjacent(const int *tuple, size_t size, int *result) {
    if (tuple == NULL || result == NULL || size < 2) {
        return -1;
    }

    for (size_t i = 0; i < size - 1; ++i) {
        result[i] = tuple[i] * tuple[i + 1];
    }

    return 0;
}

int main(void) {
    size_t size = 5;
    int *tuple = malloc(size * sizeof(int));
    
    if (tuple == NULL) {
        return EXIT_FAILURE;
    }

    tuple[0] = 2;
    tuple[1] = 3;
    tuple[2] = 4;
    tuple[3] = 5;
    tuple[4] = 6;

    int *result = malloc((size - 1) * sizeof(int));
    if (result == NULL) {
        free(tuple);
        return EXIT_FAILURE;
    }

    if (multiply_adjacent(tuple, size, result) != 0) {
        free(result);
        free(tuple);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < size - 1; ++i) {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(result);
    free(tuple);

    return EXIT_SUCCESS;
}