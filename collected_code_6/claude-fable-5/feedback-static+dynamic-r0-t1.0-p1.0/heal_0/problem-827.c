#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int sum_column(const int *const *matrix, size_t rows, size_t cols, size_t column, long *result)
{
    size_t i;
    long sum = 0;

    if (matrix == NULL || result == NULL) {
        return -1;
    }

    if (column >= cols) {
        return -1;
    }

    for (i = 0; i < rows; i++) {
        if (matrix[i] == NULL) {
            return -1;
        }
        if ((matrix[i][column] > 0 && sum > LONG_MAX - matrix[i][column]) ||
            (matrix[i][column] < 0 && sum < LONG_MIN - matrix[i][column])) {
            return -1;
        }
        sum += matrix[i][column];
    }

    *result = sum;
    return 0;
}

int main(void)
{
    size_t rows = 3;
    size_t cols = 4;
    size_t i;
    size_t j;
    long result = 0;
    int **matrix;
    int status = EXIT_SUCCESS;

    matrix = malloc(rows * sizeof(*matrix));
    if (matrix == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < rows; i++) {
        matrix[i] = malloc(cols * sizeof(*matrix[i]));
        if (matrix[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            for (j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            return EXIT_FAILURE;
        }
        for (j = 0; j < cols; j++) {
            matrix[i][j] = (int)(i * cols + j + 1);
        }
    }

    if (sum_column((const int *const *)matrix, rows, cols, 2, &result) == 0) {
        printf("Sum of column 2: %ld\n", result);
    } else {
        fprintf(stderr, "Failed to compute column sum\n");
        status = EXIT_FAILURE;
    }

    for (i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return status;
}