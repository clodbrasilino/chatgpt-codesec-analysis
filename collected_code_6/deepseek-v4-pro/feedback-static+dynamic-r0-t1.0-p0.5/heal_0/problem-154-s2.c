#include <stdio.h>
#include <stdlib.h>

int** extract_elements(int** matrix, int rows, int cols, int* indices, int indices_count, int** result_rows, int** result_cols) {
    if (matrix == NULL || indices == NULL || result_rows == NULL || result_cols == NULL || rows <= 0 || cols <= 0 || indices_count <= 0) {
        return NULL;
    }
    
    int** result = (int**)malloc(indices_count * sizeof(int*));
    if (result == NULL) {
        return NULL;
    }
    
    *result_rows = (int*)malloc(indices_count * sizeof(int));
    if (*result_rows == NULL) {
        free(result);
        return NULL;
    }
    
    *result_cols = (int*)malloc(indices_count * sizeof(int));
    if (*result_cols == NULL) {
        free(*result_rows);
        free(result);
        return NULL;
    }
    
    for (int i = 0; i < indices_count; i++) {
        int idx = indices[i];
        if (idx < 0 || idx >= rows * cols) {
            free(*result_cols);
            free(*result_rows);
            free(result);
            return NULL;
        }
        
        int row = idx / cols;
        int col = idx % cols;
        
        result[i] = (int*)malloc(sizeof(int));
        if (result[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(result[j]);
            }
            free(*result_cols);
            free(*result_rows);
            free(result);
            return NULL;
        }
        
        *result[i] = matrix[row][col];
        (*result_rows)[i] = row;
        (*result_cols)[i] = col;
    }
    
    return result;
}

int main() {
    int rows = 3;
    int cols = 4;
    
    int** matrix = (int**)malloc(rows * sizeof(int*));
    if (matrix == NULL) {
        return 1;
    }
    
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
        if (matrix[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            return 1;
        }
    }
    
    int value = 1;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = value++;
        }
    }
    
    int indices[] = {0, 5, 7, 11};
    int indices_count = 4;
    int* result_rows = NULL;
    int* result_cols = NULL;
    
    int** extracted = extract_elements(matrix, rows, cols, indices, indices_count, &result_rows, &result_cols);
    
    if (extracted != NULL) {
        for (int i = 0; i < indices_count; i++) {
            printf("Element at (%d,%d): %d\n", result_rows[i], result_cols[i], *extracted[i]);
        }
        
        for (int i = 0; i < indices_count; i++) {
            free(extracted[i]);
        }
        free(extracted);
        free(result_rows);
        free(result_cols);
    }
    
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
    
    return 0;
}