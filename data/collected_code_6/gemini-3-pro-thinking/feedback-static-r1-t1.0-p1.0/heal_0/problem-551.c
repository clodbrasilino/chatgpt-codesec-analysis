#include <stdio.h>
#include <stdlib.h>

int* extract_column(int **matrix, size_t rows, size_t cols, size_t col_index);
void free_matrix(int **matrix, size_t rows);

int* extract_column(int **matrix, size_t rows, size_t cols, size_t col_index) {
    if (matrix == NULL || col_index >= cols || rows == 0) {
        return NULL;
    }

    int *column = (int *)malloc(rows * sizeof(int));
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

void free_matrix(int **matrix, size_t rows) {
    if (matrix == NULL) {
        return;
    }
    for (size_t i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main(void) {
    size_t rows = 4;
    size_t cols = 5;
    size_t target_col = 2;

    int **matrix = (int **)malloc(rows * sizeof(int *));
    if (matrix == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < rows; i++) {
        matrix[i] = (int *)malloc(cols * sizeof(int));
        if (matrix[i] == NULL) {
            free_matrix(matrix, i);
            return EXIT_FAILURE;
        }
        for (size_t j = 0; j < cols; j++) {
            matrix[i][j] = (int)((i * cols) + j);
        }
    }

    int *extracted = extract_column(matrix, rows, cols, target_col);
    if (extracted == NULL) {
        free_matrix(matrix, rows);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < rows; i++) {
        printf("%d\n", extracted[i]);
    }

    free(extracted);
    free_matrix(matrix, rows);

    return EXIT_SUCCESS;
}