#include <stdio.h>
#include <stdlib.h>

void free_matrix(int **matrix, int rows) {
    if (matrix == NULL) {
        return;
    }
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int remove_column(int **matrix, int rows, int *cols, int col) {
    if (matrix == NULL || rows <= 0 || cols == NULL || *cols <= 0 || col < 0 || col >= *cols) {
        return -1;
    }

    int new_cols = *cols - 1;
    int **new_rows = malloc((size_t)rows * sizeof(int *));
    if (new_rows == NULL) {
        return -1;
    }

    for (int i = 0; i < rows; i++) {
        if (matrix[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(new_rows[j]);
            }
            free(new_rows);
            return -1;
        }

        if (new_cols > 0) {
            new_rows[i] = malloc((size_t)new_cols * sizeof(int));
            if (new_rows[i] == NULL) {
                for (int j = 0; j < i; j++) {
                    free(new_rows[j]);
                }
                free(new_rows);
                return -1;
            }
        } else {
            new_rows[i] = NULL;
        }

        int dest = 0;
        for (int j = 0; j < *cols; j++) {
            if (j == col) {
                continue;
            }
            new_rows[i][dest] = matrix[i][j];
            dest++;
        }
    }

    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
        matrix[i] = new_rows[i];
    }
    free(new_rows);

    *cols = new_cols;
    return 0;
}

int main(void) {
    int rows = 3;
    int cols = 4;

    int **matrix = malloc((size_t)rows * sizeof(int *));
    if (matrix == NULL) {
        return EXIT_FAILURE;
    }

    for (int i = 0; i < rows; i++) {
        matrix[i] = malloc((size_t)cols * sizeof(int));
        if (matrix[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            return EXIT_FAILURE;
        }

        for (int j = 0; j < cols; j++) {
            matrix[i][j] = i * cols + j + 1;
        }
    }

    if (remove_column(matrix, rows, &cols, 1) != 0) {
        fprintf(stderr, "Failed to remove column\n");
        free_matrix(matrix, rows);
        return EXIT_FAILURE;
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    free_matrix(matrix, rows);
    return EXIT_SUCCESS;
}