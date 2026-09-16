#include <stdio.h>
#include <stdlib.h>

int sum_column(int **matrix, size_t rows, size_t cols, size_t col_index, long *result)
{
    if (matrix == NULL || result == NULL) {
        return -1;
    }
    if (col_index >= cols) {
        return -2;
    }

    long sum = 0;
    for (size_t i = 0; i < rows; i++) {
        if (matrix[i] == NULL) {
            return -3;
        }
        sum += matrix[i][col_index];
    }

    *result = sum;
    return 0;
}

int main(void)
{
    const size_t rows = 3;
    const size_t cols = 4;

    int **matrix = malloc(rows * sizeof *matrix);
    if (matrix == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < rows; i++) {
        matrix[i] = malloc(cols * sizeof *matrix[i]);
        if (matrix[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            for (size_t j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            return EXIT_FAILURE;
        }
    }

    const int values[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            matrix[i][j] = values[i][j];
        }
    }

    const size_t col_index = 2;
    long result = 0;

    int status = sum_column(matrix, rows, cols, col_index, &result);
    if (status != 0) {
        fprintf(stderr, "Failed to sum column (error %d)\n", status);
        for (size_t i = 0; i < rows; i++) {
            free(matrix[i]);
        }
        free(matrix);
        return EXIT_FAILURE;
    }

    printf("Sum of column %zu: %ld\n", col_index, result);

    for (size_t i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return EXIT_SUCCESS;
}