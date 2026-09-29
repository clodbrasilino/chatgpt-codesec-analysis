#include <stdio.h>
#include <stdlib.h>

void free_matrix(int **matrix, size_t rows) {
    if (!matrix) {
        return;
    }
    for (size_t i = 0; i < rows; ++i) {
        free(matrix[i]);
    }
    free(matrix);
}

int **remove_column(int **matrix, size_t rows, size_t cols, size_t col_to_remove) {
    if (!matrix || rows == 0 || cols <= 1 || col_to_remove >= cols) {
        return NULL;
    }

    int **new_matrix = (int **)malloc(rows * sizeof(int *));
    if (!new_matrix) {
        return NULL;
    }

    for (size_t i = 0; i < rows; ++i) {
        if (!matrix[i]) {
            free_matrix(new_matrix, i);
            return NULL;
        }

        new_matrix[i] = (int *)malloc((cols - 1) * sizeof(int));
        if (!new_matrix[i]) {
            free_matrix(new_matrix, i);
            return NULL;
        }

        size_t new_col_idx = 0;
        for (size_t j = 0; j < cols; ++j) {
            if (j != col_to_remove) {
                new_matrix[i][new_col_idx++] = matrix[i][j];
            }
        }
    }

    return new_matrix;
}

int main(void) {
    size_t rows = 3;
    size_t cols = 4;
    size_t col_to_remove = 1;

    int **matrix = (int **)malloc(rows * sizeof(int *));
    if (!matrix) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < rows; ++i) {
        matrix[i] = (int *)malloc(cols * sizeof(int));
        if (!matrix[i]) {
            free_matrix(matrix, i);
            return EXIT_FAILURE;
        }
        for (size_t j = 0; j < cols; ++j) {
            matrix[i][j] = (int)(i * cols + j);
        }
    }

    int **new_matrix = remove_column(matrix, rows, cols, col_to_remove);
    if (!new_matrix) {
        free_matrix(matrix, rows);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols - 1; ++j) {
            printf("%d ", new_matrix[i][j]);
        }
        printf("\n");
    }

    free_matrix(new_matrix, rows);
    free_matrix(matrix, rows);

    return EXIT_SUCCESS;
}