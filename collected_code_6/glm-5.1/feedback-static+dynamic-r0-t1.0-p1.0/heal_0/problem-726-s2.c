#include <stdio.h>
#include <stdlib.h>

int *multiply_adjacent(const int *tuple, size_t size) {
    if (size < 2) {
        return NULL;
    }

    size_t result_size = size - 1;
    int *result = (int *)malloc(result_size * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < result_size; i++) {
        result[i] = tuple[i] * tuple[i + 1];
    }

    return result;
}

int main(void) {
    int tuple[] = {2, 3, 4, 5};
    size_t size = sizeof(tuple) / sizeof(tuple[0]);

    int *result = multiply_adjacent(tuple, size);
    if (result == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < size - 1; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(result);

    return EXIT_SUCCESS;
}