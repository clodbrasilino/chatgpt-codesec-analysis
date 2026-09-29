#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int **remove_similar_rows(int **matrix, int rows, int cols, int *out_rows) {
    *out_rows = 0;
    if (rows <= 0 || cols <= 0) {
        return NULL;
    }

    int *keep = (int *)malloc(rows * sizeof(int));
    if (!keep) {
        return NULL;
    }
    for (int i = 0; i < rows; i++) {
        keep[i] = 1;
    }

    for (int i = 0; i < rows; i++) {
        if (!keep[i]) {
            continue;
        }
        for (int j = i + 1; j < rows; j++) {
            if (!keep[j]) {
                continue;
            }
            int is_duplicate = 1;
            for (int k = 0; k < cols; k++) {
                if (matrix[i][k] != matrix[j][k]) {
                    is_duplicate = 0;
                    break;
                }
            }
            if (is_duplicate) {
                keep[j] = 0;
            }
        }
    }

    for (int i = 0; i < rows; i++) {
        if (keep[i]) {
            (*out_rows)++;
        }
    }

    if (*out_rows == 0) {
        free(keep);
        return NULL;
    }

    int **result = (int **)malloc(*out_rows * sizeof(int *));
    if (!result) {
        free(keep);
        return NULL;
    }

    int r = 0;
    for (int i = 0; i < rows; i++) {
        if (keep[i]) {
            result[r] = (int *)malloc(cols * sizeof(int));
            if (!result[r]) {
                for (int p = 0; p < r; p++) {
                    free(result[p]);
                }
                free(result);
                free(keep);
                return NULL;
            }
            for (int k = 0; k < cols; k++) {
                result[r][k] = matrix[i][k];
            }
            r++;
        }
    }

    free(keep);
    return result;
}

void free_matrix(int **matrix, int rows) {
    if (!matrix) {
        return;
    }
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main(void) {
    int rows = 5;
    int cols = 3;

    int raw_data[5][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {1, 2, 3},
        {7, 8, 9},
        {4, 5, 6}
    };

    int **matrix = (int **)malloc(rows * sizeof(int *));
    if (!matrix) {
        return 1;
    }
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int *)malloc(cols * sizeof(int));
        if (!matrix[i]) {
            for (int j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            return 1;
        }
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = raw_data[i][j];
        }
    }

    int out_rows = 0;
    int **unique_matrix = remove_similar_rows(matrix, rows, cols, &out_rows);

    for (int i = 0; i < out_rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", unique_matrix[i][j]);
        }
        printf("\n");
    }

    free_matrix(matrix, rows);
    free_matrix(unique_matrix, out_rows);

    return 0;
}