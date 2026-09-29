#include <stdio.h>
#include <stdlib.h>

void sort_matrix_by_row_sum(int **matrix, int rows, int cols) {
    if (matrix == NULL || rows <= 0 || cols <= 0) {
        return;
    }

    int *row_sums = (int *)malloc(rows * sizeof(int));
    if (row_sums == NULL) {
        return;
    }

    for (int i = 0; i < rows; i++) {
        row_sums[i] = 0;
        for (int j = 0; j < cols; j++) {
            row_sums[i] += matrix[i][j];
        }
    }

    for (int i = 0; i < rows - 1; i++) {
        for (int j = 0; j < rows - i - 1; j++) {
            if (row_sums[j] > row_sums[j + 1]) {
                int temp_sum = row_sums[j];
                row_sums[j] = row_sums[j + 1];
                row_sums[j + 1] = temp_sum;

                int *temp_row = matrix[j];
                matrix[j] = matrix[j + 1];
                matrix[j + 1] = temp_row;
            }
        }
    }

    free(row_sums);
}

void print_matrix(int **matrix, int rows, int cols) {
    if (matrix == NULL) {
        return;
    }
    for (int i = 0; i < rows; i++) {
        if (matrix[i] == NULL) {
            continue;
        }
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main(void) {
    int rows = 4;
    int cols = 3;
    
    int **matrix = (int **)malloc(rows * sizeof(int *));
    if (matrix == NULL) {
        return 1;
    }

    for (int i = 0; i < rows; i++) {
        matrix[i] = (int *)malloc(cols * sizeof(int));
        if (matrix[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            return 1;
        }
    }

    matrix[0][0] = 3; matrix[0][1] = 2; matrix[0][2] = 1;
    matrix[1][0] = 9; matrix[1][1] = 8; matrix[1][2] = 7;
    matrix[2][0] = 1; matrix[2][1] = 1; matrix[2][2] = 1;
    matrix[3][0] = 5; matrix[3][1] = 5; matrix[3][2] = 5;

    printf("Original matrix:\n");
    print_matrix(matrix, rows, cols);

    sort_matrix_by_row_sum(matrix, rows, cols);

    printf("\nSorted matrix by row sum:\n");
    print_matrix(matrix, rows, cols);

    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}