#include <stdio.h>
#include <stdlib.h>

int* calculate_row_sums(int** matrix, int rows, int cols) {
    int* sums = (int*)malloc(rows * sizeof(int));
    if (sums == NULL) {
        return NULL;
    }
    for (int i = 0; i < rows; i++) {
        sums[i] = 0;
        for (int j = 0; j < cols; j++) {
            sums[i] += matrix[i][j];
        }
    }
    return sums;
}

void sort_matrix_by_row_sums(int** matrix, int rows, int cols) {
    if (matrix == NULL || rows <= 0 || cols <= 0) {
        return;
    }
    
    int* sums = calculate_row_sums(matrix, rows, cols);
    if (sums == NULL) {
        return;
    }
    
    for (int i = 0; i < rows - 1; i++) {
        for (int j = 0; j < rows - i - 1; j++) {
            if (sums[j] > sums[j + 1]) {
                int temp_sum = sums[j];
                sums[j] = sums[j + 1];
                sums[j + 1] = temp_sum;
                
                int* temp_row = matrix[j];
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
    
    int** matrix = (int**)malloc(rows * sizeof(int*));
    if (matrix == NULL) {
        return EXIT_FAILURE;
    }
    
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
        if (matrix[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            return EXIT_FAILURE;
        }
    }
    
    matrix[0][0] = 1; matrix[0][1] = 2; matrix[0][2] = 3;
    matrix[1][0] = 4; matrix[1][1] = 5; matrix[1][2] = 6;
    matrix[2][0] = 7; matrix[2][1] = 8; matrix[2][2] = 9;
    matrix[3][0] = 1; matrix[3][1] = 1; matrix[3][2] = 1;
    
    sort_matrix_by_row_sums(matrix, rows, cols);
    
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