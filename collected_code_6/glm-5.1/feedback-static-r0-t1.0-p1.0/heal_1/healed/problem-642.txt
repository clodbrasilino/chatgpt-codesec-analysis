#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int **remove_similar_rows(int **matrix, int rows, int cols, int *out_rows) {
    if (matrix == NULL || out_rows == NULL || rows <= 0 || cols <= 0) {
        if (out_rows != NULL) *out_rows = 0;
        return NULL;
    }

    int *keep = malloc(rows * sizeof(int));
    if (keep == NULL) {
        *out_rows = 0;
        return NULL;
    }

    for (int i = 0; i < rows; i++) {
        keep[i] = 1;
    }

    for (int i = 0; i < rows; i++) {
        if (!keep[i]) continue;
        for (int j = i + 1; j < rows; j++) {
            if (!keep[j]) continue;
            int is_similar = 1;
            for (int k = 0; k < cols; k++) {
                if (matrix[i][k] != matrix[j][k]) {
                    is_similar = 0;
                    break;
                }
            }
            if (is_similar) {
                keep[j] = 0;
            }
        }
    }

    int count = 0;
    for (int i = 0; i < rows; i++) {
        if (keep[i]) count++;
    }

    if (count == 0) {
        free(keep);
        *out_rows = 0;
        return NULL;
    }

    int **result = malloc(count * sizeof(int *));
    if (result == NULL) {
        free(keep);
        *out_rows = 0;
        return NULL;
    }

    int idx = 0;
    for (int i = 0; i < rows; i++) {
        if (keep[i]) {
            result[idx] = malloc(cols * sizeof(int));
            if (result[idx] == NULL) {
                for (int e = 0; e < idx; e++) {
                    free(result[e]);
                }
                free(result);
                free(keep);
                *out_rows = 0;
                return NULL;
            }
            memcpy(result[idx], matrix[i], cols * sizeof(int));
            idx++;
        }
    }

    free(keep);
    *out_rows = count;
    return result;
}

int main() {
    int rows = 5;
    int cols = 3;

    int **matrix = malloc(rows * sizeof(int *));
    if (matrix == NULL) return 1;

    const int data[5][3] = {{1, 2, 3}, {4, 5, 6}, {1, 2, 3}, {7, 8, 9}, {4, 5, 6}};
    for (int i = 0; i < rows; i++) {
        matrix[i] = malloc(cols * sizeof(int));
        if (matrix[i] == NULL) {
            for (int e = 0; e < i; e++) {
                free(matrix[e]);
            }
            free(matrix);
            return 1;
        }
        memcpy(matrix[i], data[i], cols * sizeof(int));
    }

    int out_rows = 0;
    int **result = remove_similar_rows(matrix, rows, cols, &out_rows);

    for (int i = 0; i < out_rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);

    for (int i = 0; i < out_rows; i++) {
        free(result[i]);
    }
    free(result);

    return 0;
}