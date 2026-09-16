#include <stdio.h>
#include <stdlib.h>

int sum_column(int **list, size_t rows, size_t cols, size_t target_col) {
    if (list == NULL || rows == 0 || cols == 0 || target_col >= cols) {
        return 0;
    }

    int sum = 0;
    for (size_t i = 0; i < rows; i++) {
        if (list[i] == NULL) {
            continue;
        }
        sum += list[i][target_col];
    }
    return sum;
}

int main(void) {
    size_t rows = 3;
    size_t cols = 4;

    int **matrix = malloc(rows * sizeof(int *));
    if (matrix == NULL) {
        return 1;
    }

    for (size_t i = 0; i < rows; i++) {
        matrix[i] = malloc(cols * sizeof(int));
        if (matrix[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            return 1;
        }
        for (size_t j = 0; j < cols; j++) {
            matrix[i][j] = (i + 1) * (j + 1);
        }
    }

    size_t target = 2;
    int result = sum_column(matrix, rows, cols, target);
    printf("%d\n", result);

    for (size_t i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}