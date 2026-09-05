#include <stdio.h>
#include <stdlib.h>

int multiply_adjacent(const int *tuple, size_t size, int **result, size_t *result_size) {
    if (tuple == NULL || result == NULL || result_size == NULL) {
        return -1;
    }
    
    if (size == 0) {
        *result = NULL;
        *result_size = 0;
        return 0;
    }
    
    if (size == 1) {
        *result_size = 0;
        *result = NULL;
        return 0;
    }
    
    *result_size = size - 1;
    *result = malloc(*result_size * sizeof(int));
    
    if (*result == NULL) {
        return -1;
    }
    
    for (size_t i = 0; i < *result_size; i++) {
        (*result)[i] = tuple[i] * tuple[i + 1];
    }
    
    return 0;
}

int main(void) {
    int tuple[] = {1, 2, 3, 4, 5};
    size_t size = sizeof(tuple) / sizeof(tuple[0]);
    int *result = NULL;
    size_t result_size = 0;
    
    if (multiply_adjacent(tuple, size, &result, &result_size) != 0) {
        fprintf(stderr, "Error: Failed to multiply adjacent elements\n");
        return EXIT_FAILURE;
    }
    
    printf("Original tuple: ");
    for (size_t i = 0; i < size; i++) {
        printf("%d ", tuple[i]);
    }
    printf("\n");
    
    printf("Result: ");
    for (size_t i = 0; i < result_size; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");
    
    free(result);
    result = NULL;
    
    return EXIT_SUCCESS;
}