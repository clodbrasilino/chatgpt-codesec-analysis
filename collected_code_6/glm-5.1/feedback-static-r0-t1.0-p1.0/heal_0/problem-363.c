#include <stdio.h>
#include <stdlib.h>

int* add_k_to_tuple(const int* tuple, size_t size, int k) {
    if (tuple == NULL) {
        return NULL;
    }

    int* result = (int*)malloc(size * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < size; ++i) {
        result[i] = tuple[i] + k;
    }

    return result;
}

int main() {
    int tuple[] = {1, 2, 3, 4, 5};
    size_t size = sizeof(tuple) / sizeof(tuple[0]);
    int k = 10;

    int* new_tuple = add_k_to_tuple(tuple, size, k);
    if (new_tuple == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < size; ++i) {
        printf("%d ", new_tuple[i]);
    }
    printf("\n");

    free(new_tuple);
    new_tuple = NULL;

    return EXIT_SUCCESS;
}