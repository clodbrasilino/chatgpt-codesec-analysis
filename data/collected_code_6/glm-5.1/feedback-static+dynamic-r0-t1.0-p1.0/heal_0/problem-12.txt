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

int main() {
    int rows = 4;
    int cols = 3;
    int** matrix = (int**)malloc(rows * sizeof(int*));
    if (matrix == NULL) {
        return 1;
    }
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
        if (matrix[i] == NULL) {
            for (int k = 0; k < i; k++) {
                free(matrix[k]);
            }
            free(matrix);
            return 1;
        }
    }
    int data[4][3] = {{1, 2, 3}, {4, 5, 6}, {1, 1, 1}, {9, 8, 7}};
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = data[i][j];
        }
    }
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
    return 0;
}