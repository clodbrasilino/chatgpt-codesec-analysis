#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int remove_column(int ***matrix, size_t rows, size_t *cols, size_t col)
{
    if (matrix == NULL || cols == NULL) {
        return -1;
    }

    if (rows == 0) {
        if (col >= *cols) {
            return -1;
        }
        (*cols)--;
        return 0;
    }

    if (*matrix == NULL || col >= *cols) {
        return -1;
    }

    size_t new_cols = *cols - 1;

    if (new_cols > 0 && new_cols > SIZE_MAX / sizeof(int)) {
        return -1;
    }

    if (rows > SIZE_MAX / sizeof(int *)) {
        return -1;
    }

    int **new_matrix = malloc(rows * sizeof(int *));
    if (new_matrix == NULL) {
        return -1;
    }

    for (size_t i = 0; i < rows; i++) {
        new_matrix[i] = NULL;
    }

    for (size_t i = 0; i < rows; i++) {
        if ((*matrix)[i] == NULL && new_cols > 0) {
            for (size_t j = 0; j < rows; j++) {
                free(new_matrix[j]);
            }
            free(new_matrix);
            return -1;
        }

        if (new_cols > 0) {
            new_matrix[i] = malloc(new_cols * sizeof(int));
            if (new_matrix[i] == NULL) {
                for (size_t j = 0; j < rows; j++) {
                    free(new_matrix[j]);
                }
                free(new_matrix);
                return -1;
            }

            size_t dest = 0;
            for (size_t src = 0; src < *cols; src++) {
                if (src == col) {
                    continue;
                }
                new_matrix[i][dest] = (*matrix)[i][src];
                dest++;
            }
        }
    }

    for (size_t i = 0; i < rows; i++) {
        free((*matrix)[i]);
    }
    free(*matrix);

    *matrix = new_matrix;
    *cols = new_cols;

    return 0;
}

int main(void)
{
    size_t rows = 3;
    size_t cols = 3;

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
            matrix[i][j] = (int)(i * cols + j + 1);
        }
    }

    if (remove_column(&matrix, rows, &cols, 1) != 0) {
        for (size_t i = 0; i < rows; i++) {
            free(matrix[i]);
        }
        free(matrix);
        return 1;
    }

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    for (size_t i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}