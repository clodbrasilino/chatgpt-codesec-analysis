#include <stdio.h>
#include <stdlib.h>

int *extract_elements(int **matrix, int rows, const int *col_sizes, const int *req_rows, const int *req_cols, int num_reqs, int *out_size) {
    if (matrix == NULL || col_sizes == NULL || req_rows == NULL || req_cols == NULL || out_size == NULL) {
        return NULL;
    }

    int valid_count = 0;
    for (int i = 0; i < num_reqs; i++) {
        int r = req_rows[i];
        int c = req_cols[i];
        if (r >= 0 && r < rows && col_sizes[r] > 0 && c >= 0 && c < col_sizes[r]) {
            valid_count++;
        }
    }

    if (valid_count == 0) {
        *out_size = 0;
        return NULL;
    }

    int *result = (int *)malloc(valid_count * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    int index = 0;
    for (int i = 0; i < num_reqs; i++) {
        int r = req_rows[i];
        int c = req_cols[i];
        if (r >= 0 && r < rows && col_sizes[r] > 0 && c >= 0 && c < col_sizes[r]) {
            result[index++] = matrix[r][c];
        }
    }

    *out_size = valid_count;
    return result;
}

int main(void) {
    int rows = 3;
    int *col_sizes = (int *)malloc(rows * sizeof(int));
    if (col_sizes == NULL) return 1;

    col_sizes[0] = 3;
    col_sizes[1] = 2;
    col_sizes[2] = 4;

    int **matrix = (int **)malloc(rows * sizeof(int *));
    if (matrix == NULL) {
        free(col_sizes);
        return 1;
    }

    for (int i = 0; i < rows; i++) {
        matrix[i] = (int *)malloc(col_sizes[i] * sizeof(int));
        if (matrix[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            free(col_sizes);
            return 1;
        }
    }

    matrix[0][0] = 1; matrix[0][1] = 2; matrix[0][2] = 3;
    matrix[1][0] = 4; matrix[1][1] = 5;
    matrix[2][0] = 6; matrix[2][1] = 7; matrix[2][2] = 8; matrix[2][3] = 9;

    int req_rows[] = {0, 1, 2, 1, 5, 2};
    int req_cols[] = {1, 0, 3, 2, 0, -1};
    int num_reqs = 6;
    int out_size = 0;

    int *result = extract_elements(matrix, rows, col_sizes, req_rows, req_cols, num_reqs, &out_size);

    if (result != NULL) {
        for (int i = 0; i < out_size; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
        free(result);
    }

    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
    free(col_sizes);

    return 0;
}