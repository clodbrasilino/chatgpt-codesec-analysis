#include <stdio.h>
#include <stdlib.h>

typedef struct {
    size_t row;
    size_t col;
} Index;

int* extract_elements(int** matrix, size_t rows, size_t cols, Index* indices, size_t num_indices, size_t* out_size) {
    if (matrix == NULL || indices == NULL || out_size == NULL) {
        return NULL;
    }
    
    int* result = (int*)malloc(num_indices * sizeof(int));
    if (result == NULL) {
        return NULL;
    }
    
    size_t count = 0;
    for (size_t i = 0; i < num_indices; i++) {
        if (indices[i].row < rows && indices[i].col < cols) {
            if (matrix[indices[i].row] != NULL) {
                result[count] = matrix[indices[i].row][indices[i].col];
                count++;
            }
        }
    }
    
    if (count == 0) {
        free(result);
        result = NULL;
    } else if (count < num_indices) {
        int* temp = (int*)realloc(result, count * sizeof(int));
        if (temp != NULL) {
            result = temp;
        }
    }
    
    *out_size = count;
    return result;
}

int main(void) {
    size_t rows = 3;
    size_t cols = 3;
    
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
        for (size_t j = 0; j < cols; j++) {
            matrix[i][j] = (int)(i * cols + j + 1);
        }
    }
    
    Index indices[5];
    indices[0].row = 0; indices[0].col = 0;
    indices[1].row = 1; indices[1].col = 1;
    indices[2].row = 2; indices[2].col = 2;
    indices[3].row = 5; indices[3].col = 5;
    indices[4].row = 0; indices[4].col = 2;
    
    size_t out_size = 0;
    int* extracted = extract_elements(matrix, rows, cols, indices, 5, &out_size);
    
    if (extracted != NULL) {
        for (size_t i = 0; i < out_size; i++) {
            printf("%d ", extracted[i]);
        }
        printf("\n");
        free(extracted);
    }
    
    for (size_t i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
    
    return EXIT_SUCCESS;
}