#include <stdio.h>
#include <stdlib.h>

int **remove_column(int **matrix, size_t rows, size_t cols, size_t col_index, size_t *new_cols)
{
    int **result = NULL;
    size_t i;
    size_t j;
    size_t k;

    if (matrix == NULL || new_cols == NULL || rows == 0U || cols == 0U || col_index >= cols) {
        return NULL;
    }

    *new_cols = cols - 1U;

    result = (int **)malloc(rows * sizeof(int *));
    if (result == NULL) {
        return NULL;
    }

    for (i = 0U; i < rows; i++) {
        if (*new_cols > 0U) {
            result[i] = (int *)malloc(*new_cols * sizeof(int));
            if (result[i] == NULL) {
                for (j = 0U; j < i; j++) {
                    free(result[j]);
                }
                free(result);
                return NULL;
            }
        } else {
            result[i] = NULL;
        }

        k = 0U;
        for (j = 0U; j < cols; j++) {
            if (j != col_index) {
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

    for (i = 0U; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main(void)
{
    size_t rows = 3U;
    size_t cols = 4U;
    size_t new_cols = 0U;
    size_t i;
    size_t j;
    int value = 1;
    int **matrix = NULL;
    int **reduced = NULL;

    matrix = (int **)malloc(rows * sizeof(int *));
    if (matrix == NULL) {
        (void)fprintf(stderr, "Allocation failure\n");
        return EXIT_FAILURE;
    }

    for (i = 0U; i < rows; i++) {
        matrix[i] = (int *)malloc(cols * sizeof(int));
        if (matrix[i] == NULL) {
            for (j = 0U; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            (void)fprintf(stderr, "Allocation failure\n");
            return EXIT_FAILURE;
        }
        for (j = 0U; j < cols; j++) {
            matrix[i][j] = value;
            value++;
        }
    }

    (void)printf("Original matrix:\n");
    for (i = 0U; i < rows; i++) {
        for (j = 0U; j < cols; j++) {
            (void)printf("%d ", matrix[i][j]);
        }
        (void)printf("\n");
    }

    reduced = remove_column(matrix, rows, cols, 1U, &new_cols);
    if (reduced == NULL) {
        free_matrix(matrix, rows);
        (void)fprintf(stderr, "Column removal failed\n");
        return EXIT_FAILURE;
    }

    (void)printf("Matrix after removing column 1:\n");
    for (i = 0U; i < rows; i++) {
        for (j = 0U; j < new_cols; j++) {
            (void)printf("%d ", reduced[i][j]);
        }
        (void)printf("\n");
    }

    free_matrix(matrix, rows);
    free_matrix(reduced, rows);

    return EXIT_SUCCESS;
}