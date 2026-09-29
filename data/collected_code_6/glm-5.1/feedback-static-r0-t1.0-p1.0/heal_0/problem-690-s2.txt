#include <stdio.h>
#include <stdlib.h>

int* multiply_consecutive(const int* list, size_t size) {
    if (list == NULL || size == 0) {
        return NULL;
    }

    int* result = (int*)malloc(size * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    result[0] = list[0];
    for (size_t i = 1; i < size; ++i) {
        result[i] = list[i] * list[i - 1];
    }

    return result;
}

int main(void) {
    int list[] = {1, 2, 3, 4, 5};
    size_t size = sizeof(list) / sizeof(list[0]);

    int* multiplied = multiply_consecutive(list, size);
    if (multiplied == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < size; ++i) {
        printf("%d ", multiplied[i]);
    }
    printf("\n");

    free(multiplied);
    multiplied = NULL;

    return EXIT_SUCCESS;
}