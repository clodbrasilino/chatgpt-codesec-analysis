#include <stdio.h>
#include <stdlib.h>

int extract_column(int **matrix, size_t rows, size_t cols, size_t col_index, int **result)
{
    size_t i;
    int *column;

    if (matrix == NULL || result == NULL || rows == 0 || col_index >= cols) {
        return -1;
    }

    column = malloc(rows * sizeof(int));
    if (column == NULL) {
        return -1;
    }

    for (i = 0; i < rows; i++) {
        if (matrix[i] == NULL) {
            free(column);
            return -1;
        }
        column[i] = matrix[i][col_index];
    }

    *result = column;
    return 0;
}

int main(void)
{
    size_t rows = 3;
    size_t cols = 4;
    size_t i;
    size_t j;
    int **matrix;
    int *column = NULL;
    int status;

    matrix = malloc(rows * sizeof(int *));
    if (matrix == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < rows; i++) {
        matrix[i] = malloc(cols * sizeof(int));
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

    printf("Matrix:\n");
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    status = extract_column(matrix, rows, cols, 2, &column);
    if (status != 0) {
        fprintf(stderr, "Failed to extract column\n");
        for (i = 0; i < rows; i++) {
            free(matrix[i]);
        }
        free(matrix);
        return EXIT_FAILURE;
    }

    printf("Extracted column 2:\n");
    for (i = 0; i < rows; i++) {
        printf("%d\n", column[i]);
    }

    free(column);
    for (i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return EXIT_SUCCESS;
}