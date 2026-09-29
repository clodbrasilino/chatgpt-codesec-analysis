#include <stdio.h>
#include <stdlib.h>

void extract_elements(int** matrix, int rows, int cols, int index, int** result, int* result_size) {
    if (matrix == NULL || result == NULL || result_size == NULL || rows <= 0 || cols <= 0 || index < 0 || index >= cols) {
        if (result_size != NULL) {
            *result_size = 0;
        }
        if (result != NULL) {
            *result = NULL;
        }
        return;
    }

    *result = (int*)malloc(rows * sizeof(int));
    if (*result == NULL) {
        *result_size = 0;
        return;
    }

    for (int i = 0; i < rows; i++) {
        if (matrix[i] != NULL) {
            (*result)[i] = matrix[i][index];
        } else {
            free(*result);
            *result = NULL;
            *result_size = 0;
            return;
        }
    }

    *result_size = rows;
}

int main(void) {
    int rows = 3;
    int cols = 3;
    
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
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = (i * cols) + j + 1; 
        }
    }

    int* extracted = NULL;
    int extracted_size = 0;
    int target_index = 0; 

    extract_elements(matrix, rows, cols, target_index, &extracted, &extracted_size);

    if (extracted != NULL && extracted_size > 0) {
        for (int i = 0; i < extracted_size; i++) {
            printf("%d ", extracted[i]);
        }
        printf("\n");
        free(extracted);
    }

    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}