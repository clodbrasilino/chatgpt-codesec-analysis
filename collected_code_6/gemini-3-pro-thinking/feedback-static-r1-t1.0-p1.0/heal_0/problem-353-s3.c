#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

int **create_matrix(size_t rows, size_t cols);
void free_matrix(int **matrix, size_t rows);
int remove_column(int ***matrix, size_t rows, size_t *cols, size_t col_to_remove);

int **create_matrix(size_t rows, size_t cols) {
    if (rows == 0 || cols == 0) {
        return NULL;
    }

    int **matrix = malloc(rows * sizeof(int *));
    if (!matrix) {
        return NULL;
    }

    for (size_t i = 0; i < rows; i++) {
        matrix[i] = malloc(cols * sizeof(int));
        if (!matrix[i]) {
            for (size_t j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            return NULL;
        }
    }

    return matrix;
}

void free_matrix(int **matrix, size_t rows) {
    if (!matrix) {
        return;
    }

    for (size_t i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int remove_column(int ***matrix, size_t rows, size_t *cols, size_t col_to_remove) {
    if (!matrix || !*matrix || !cols || *cols == 0 || col_to_remove >= *cols) {
        return -1;
    }

    size_t new_cols = *cols - 1;

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = col_to_remove; j < new_cols; j++) {
            (*matrix)[i][j] = (*matrix)[i][j + 1];
        }

        if (new_cols > 0) {
            int *new_row = realloc((*matrix)[i], new_cols * sizeof(int));
            if (!new_row) {
                return -1;
            }
            (*matrix)[i] = new_row;
        } else {
            free((*matrix)[i]);
            (*matrix)[i] = NULL;
        }
    }

    *cols = new_cols;
    return 0;
}

int main(void) {
    size_t rows = 3;
    size_t cols = 4;

    int **matrix = create_matrix(rows, cols);
    if (!matrix) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            matrix[i][j] = (int)(i * cols + j);
        }
    }

    if (remove_column(&matrix, rows, &cols, 1) != 0) {
        free_matrix(matrix, rows);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    free_matrix(matrix, rows);
    return EXIT_SUCCESS;
}