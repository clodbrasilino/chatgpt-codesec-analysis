#include <stdio.h>
#include <stdlib.h>

int **remove_column(int **matrix, size_t rows, size_t cols, size_t col_to_remove, size_t *new_cols)
{
    int **result;
    size_t i;
    size_t j;
    size_t k;

    if (matrix == NULL || new_cols == NULL || rows == 0 || cols == 0 || col_to_remove >= cols) {
        return NULL;
    }

    *new_cols = cols - 1U;

    result = malloc(rows * sizeof(int *));
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < rows; i++) {
        if (*new_cols == 0U) {
            result[i] = NULL;
            continue;
        }
        result[i] = malloc(*new_cols * sizeof(int));
        if (result[i] == NULL) {
            for (j = 0; j < i; j++) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }
        k = 0;
        for (j = 0; j < cols; j++) {
            if (j != col_to_remove) {
                result[i][k] = matrix[i][j];
                k++;
            }
        }
    }

    return result;
}

void free_matrix(int **matrix, size_t rows)
{
    size_t i;

    if (matrix == NULL) {
        return;
    }
    for (i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main(void)
{
    size_t rows = 3;
    size_t cols = 4;
    size_t new_cols = 0;
    size_t i;
    size_t j;
    int **matrix;
    int **reduced;
    int value = 1;

    matrix = malloc(rows * sizeof(int *));
    if (matrix == NULL) {
        return EXIT_FAILURE;
    }

    for (i = 0; i < rows; i++) {
        matrix[i] = malloc(cols * sizeof(int));
        if (matrix[i] == NULL) {
            free_matrix(matrix, i);
            return EXIT_FAILURE;
        }
        for (j = 0; j < cols; j++) {
            matrix[i][j] = value;
            value++;
        }
    }

    printf("Original matrix:\n");
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    reduced = remove_column(matrix, rows, cols, 1, &new_cols);
    if (reduced == NULL) {
        free_matrix(matrix, rows);
        return EXIT_FAILURE;
    }

    printf("Matrix after removing column 1:\n");
    for (i = 0; i < rows; i++) {
        for (j = 0; j < new_cols; j++) {
            printf("%d ", reduced[i][j]);
        }
        printf("\n");
    }

    free_matrix(matrix, rows);
    free_matrix(reduced, rows);

    return EXIT_SUCCESS;
}