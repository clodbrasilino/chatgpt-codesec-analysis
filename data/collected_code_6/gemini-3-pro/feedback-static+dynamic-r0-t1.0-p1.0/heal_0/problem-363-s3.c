#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

int* add_k_to_elements(const int* tuple, size_t size, int k) {
    if (tuple == NULL || size == 0) {
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

int main(void) {
    int original_tuple[] = {1, 2, 3, 4, 5};
    size_t size = sizeof(original_tuple) / sizeof(original_tuple[0]);
    int k = 10;

    int* new_tuple = add_k_to_elements(original_tuple, size, k);
    if (new_tuple == NULL) {
        fprintf(stderr, "Memory allocation failed or invalid input.\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < size; ++i) {
        printf("%d ", new_tuple[i]);
    }
    printf("\n");

    free(new_tuple);

    return EXIT_SUCCESS;
}