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

    for (size_t i = 0; i < size - 1; ++i) {
        result[i] = tuple[i] * tuple[i + 1];
    }

    return result;
}

int main(void) {
    int data[] = {2, 3, 4, 5};
    size_t size = sizeof(data) / sizeof(data[0]);

    int* result = multiply_adjacent(data, size);
    if (result == NULL) {
        return 1;
    }

    for (size_t i = 0; i < size - 1; ++i) {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(result);
    result = NULL;

    return 0;
}