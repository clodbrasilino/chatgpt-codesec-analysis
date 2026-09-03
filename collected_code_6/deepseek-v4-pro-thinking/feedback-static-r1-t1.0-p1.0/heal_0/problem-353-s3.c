#include <stdio.h>
#include <stdlib.h>

int **remove_column(int **list, int rows, int cols, int col_index, int *new_cols) {
    if (list == NULL || rows <= 0 || cols <= 0 || col_index < 0 || col_index >= cols || new_cols == NULL) {
        return NULL;
    }

    int result_cols = cols - 1;
    int **result = malloc((size_t)rows * sizeof(*result));
    if (result == NULL) {
        return NULL;
    }

    for (int i = 0; i < rows; i++) {
        if (list[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }

        if (result_cols > 0) {
            result[i] = malloc((size_t)result_cols * sizeof(*result[i]));
            if (result[i] == NULL) {
                for (int j = 0; j < i; j++) {
                    free(result[j]);
                }
                free(result);
                return NULL;
            }

            int write = 0;
            for (int j = 0; j < cols; j++) {
                if (j == col_index) {
                    continue;
                }
                result[i][write] = list[i][j];
                write++;
            }
        } else {
            result[i] = NULL;
        }
    }

    *new_cols = result_cols;
    return result;
}

void free_matrix(int **matrix, int rows) {
    if (matrix == NULL) {
        return;
    }

    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main(void) {
    int rows = 3;
    int cols = 4;

    int **list = malloc((size_t)rows * sizeof(*list));
    if (list == NULL) {
        return 1;
    }

    for (int i = 0; i < rows; i++) {
        list[i] = malloc((size_t)cols * sizeof(*list[i]));
        if (list[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(list[j]);
            }
            free(list);
            return 1;
        }

        for (int j = 0; j < cols; j++) {
            list[i][j] = i * cols + j + 1;
        }
    }

    int new_cols = 0;
    int **result = remove_column(list, rows, cols, 2, &new_cols);
    if (result == NULL) {
        free_matrix(list, rows);
        return 1;
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < new_cols; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }

    free_matrix(list, rows);
    free_matrix(result, rows);

    return 0;
}