#include <stdio.h>
#include <stdlib.h>

void sort_matrix_by_row_sum(int **matrix, int rows, int cols) {
    if (matrix == NULL || rows <= 0 || cols <= 0) {
        return;
    }
    
    int *sums = (int *)malloc((size_t)rows * sizeof(int));
    if (sums == NULL) {
        return;
    }
    
    for (int i = 0; i < rows; i++) {
        if (matrix[i] == NULL) {
            free(sums);
            return;
        }
        sums[i] = 0;
        for (int j = 0; j < cols; j++) {
            sums[i] += matrix[i][j];
        }
    }
    
    for (int i = 0; i < rows - 1; i++) {
        for (int j = 0; j < rows - i - 1; j++) {
            if (sums[j] > sums[j + 1]) {
                int temp_sum = sums[j];
                sums[j] = sums[j + 1];
                sums[j + 1] = temp_sum;
                
                int *temp_row = matrix[j];
                matrix[j] = matrix[j + 1];
                matrix[j + 1] = temp_row;
            }
        }
    }
    
    free(sums);
}

int main(void) {
    int rows = 4;
    int cols = 3;
    
    int **matrix = (int **)malloc((size_t)rows * sizeof(int *));
    if (matrix == NULL) {
        return EXIT_FAILURE;
    }
    
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int *)malloc((size_t)cols * sizeof(int));
        if (matrix[i] == NULL) {
            for (int k = 0; k < i; k++) {
                free(matrix[k]);
            }
            free(matrix);
            return EXIT_FAILURE;
        }
    }
    
    int values[4][3] = {
        {9, 8, 7},
        {1, 2, 3},
        {4, 5, 6},
        {0, 1, 2}
    };
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = values[i][j];
        }
    }
    
    printf("Original matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    
    sort_matrix_by_row_sum(matrix, rows, cols);
    
    printf("\nSorted matrix by row sum:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
    
    return EXIT_SUCCESS;
}