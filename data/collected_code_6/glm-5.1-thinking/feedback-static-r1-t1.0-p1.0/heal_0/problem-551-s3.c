#include <stdio.h>
#include <stdlib.h>

int* extract_column(int** matrix, size_t rows, size_t cols, size_t col_index, size_t* out_size) {
    if (matrix == NULL || out_size == NULL || rows == 0 || cols == 0 || col_index >= cols) {
        if (out_size != NULL) {
            *out_size = 0;
        }
        return NULL;
    }

    for (size_t i = 0; i < rows; i++) {
        if (matrix[i] == NULL) {
            *out_size = 0;
            return NULL;
        }
    }

    int* column = (int*)malloc(rows * sizeof(int));
    if (column == NULL) {
        *out_size = 0;
        return NULL;
    }

    for (size_t i = 0; i < rows; i++) {
        column[i] = matrix[i][col_index];
    }

    *out_size = rows;
    return column;
}

int main(void) {
    size_t rows = 3;
    size_t cols = 4;

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
            matrix[i][j] = (int)(i * cols + j);
        }
    }

    size_t col_size = 0;
    size_t target_col = 2;
    int* column = extract_column(matrix, rows, cols, target_col, &col_size);

    if (column != NULL) {
        for (size_t i = 0; i < col_size; i++) {
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