#include <stdio.h>
#include <stdlib.h>

int* extract_elements(int** matrix, size_t rows, size_t cols, size_t index, size_t* result_size) {
    if (matrix == NULL || result_size == NULL || index >= cols) {
        return NULL;
    }
    
    if (rows == 0) {
        *result_size = 0;
        return NULL;
    }
    
    int* result = (int*)malloc(rows * sizeof(int));
    if (result == NULL) {
        return NULL;
    }
    
    for (size_t i = 0; i < rows; i++) {
        if (matrix[i] == NULL) {
            free(result);
            return NULL;
        }
        result[i] = matrix[i][index];
    }
    
    *result_size = rows;
    return result;
}

int main(void) {
    size_t rows = 3;
    size_t cols = 4;
    size_t index = 0;
    size_t result_size = 0;
    
    int** matrix = (int**)malloc(rows * sizeof(int*));
    if (matrix == NULL) {
        return EXIT_FAILURE;
    }
    
    for (size_t i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
        if (matrix[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            return EXIT_FAILURE;
        }
    }
    
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            matrix[i][j] = (int)(i * cols + j + 1);
        }
    }
    
    printf("Matrix:\n");
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    
    int* extracted = extract_elements(matrix, rows, cols, index, &result_size);
    if (extracted != NULL) {
        printf("\nExtracted elements (column %zu):\n", index);
        for (size_t i = 0; i < result_size; i++) {
            printf("%d ", extracted[i]);
        }
        printf("\n");
        free(extracted);
    } else {
        fprintf(stderr, "Extraction failed\n");
    }
    
    for (size_t i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
    
    return EXIT_SUCCESS;
}