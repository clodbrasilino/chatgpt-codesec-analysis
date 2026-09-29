#include <stdio.h>
#include <stdlib.h>

int* get_column(int** matrix, size_t rows, size_t cols, size_t col_index) {
    if (matrix == NULL || rows == 0 || cols == 0 || col_index >= cols) {
        return NULL;
    }

    int* column = (int*)malloc(rows * sizeof(int));
    if (column == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < rows; i++) {
        if (matrix[i] == NULL) {
            free(column);
            return NULL;
        }
        column[i] = matrix[i][col_index];
    }

    return column;
}

int main(void) {
    size_t rows = 3;
    size_t cols = 4;
    size_t target_col = 1;

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
            matrix[i][j] = (int)((i * cols) + j);
        }
    }

    int* column = get_column(matrix, rows, cols, target_col);
    if (column != NULL) {
        for (size_t i = 0; i < rows; i++) {
            printf("%d\n", column[i]);
        }
        free(column);
    }

    for (size_t i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return EXIT_SUCCESS;
}