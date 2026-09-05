#include <stdio.h>
#include <stdlib.h>

int* calculate_row_sums(int** matrix, int rows, int cols) {
    int* sums = (int*)malloc(rows * sizeof(int));
    if (!sums) {
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

void swap_rows(int* row1, int* row2, int cols) {
    for (int i = 0; i < cols; i++) {
        int temp = row1[i];
        row1[i] = row2[i];
        row2[i] = temp;
    }
}

void sort_matrix_by_row_sum(int** matrix, int rows, int cols) {
    if (!matrix || rows <= 0 || cols <= 0) {
        return;
    }
    int* sums = calculate_row_sums(matrix, rows, cols);
    if (!sums) {
        return;
    }
    for (int i = 0; i < rows - 1; i++) {
        for (int j = 0; j < rows - i - 1; j++) {
            if (sums[j] > sums[j + 1]) {
                int temp_sum = sums[j];
                sums[j] = sums[j + 1];
                sums[j + 1] = temp_sum;
                swap_rows(matrix[j], matrix[j + 1], cols);
            }
        }
    }
    free(sums);
}

int main(void) {
    int rows = 4;
    int cols = 4;
    int** matrix = (int**)malloc(rows * sizeof(int*));
    if (!matrix) {
        return 1;
    }
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
        if (!matrix[i]) {
            for (int k = 0; k < i; k++) {
                free(matrix[k]);
            }
            free(matrix);
            return 1;
        }
    }

    int values[4][4] = {
        {1, 2, 3, 4},
        {10, 20, 30, 40},
        {5, 6, 7, 8},
        {1, 1, 1, 1}
    };

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = values[i][j];
        }
    }

    sort_matrix_by_row_sum(matrix, rows, cols);

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