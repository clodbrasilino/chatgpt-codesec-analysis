#include <stdio.h>
#include <stdlib.h>

int* multiply_adjacent(const int* tuple, size_t size) {
    if (tuple == NULL || size < 2) {
        return NULL;
    }

    int* result = (int*)malloc((size - 1) * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < size - 1; i++) {
        result[i] = tuple[i] * tuple[i + 1];
    }

    return result;
}

int main(void) {
    int tuple[] = {1, 2, 3, 4, 5};
    size_t size = sizeof(tuple) / sizeof(tuple[0]);

    int* result = multiply_adjacent(tuple, size);
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed or invalid input.\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < size - 1; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(result);

    return EXIT_SUCCESS;
}