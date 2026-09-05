#include <stdio.h>
#include <stdlib.h>

int* extract_elements(int** matrix, int rows, int cols, int* indices, int num_indices, int* out_size) {
    if (!matrix || !indices || !out_size) {
        if (out_size) *out_size = 0;
        return NULL;
    }

    int* result = (int*)malloc(num_indices * sizeof(int));
    if (!result) {
        *out_size = 0;
        return NULL;
    }

    int count = 0;
    for (int i = 0; i < num_indices; i++) {
        int idx = indices[i];
        int r = idx / cols;
        int c = idx % cols;

        if (r >= 0 && r < rows && c >= 0 && c < cols) {
            result[count++] = matrix[r][c];
        }
    }

    if (count == 0) {
        free(result);
        *out_size = 0;
        return NULL;
    }

    int* trimmed = (int*)realloc(result, count * sizeof(int));
    if (trimmed) {
        result = trimmed;
    }

    *out_size = count;
    return result;
}

int main() {
    int rows = 3;
    int cols = 3;

    int** matrix = (int**)malloc(rows * sizeof(int*));
    if (!matrix) return 1;

    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
        if (!matrix[i]) {
            for (int j = 0; j < i; j++) free(matrix[j]);
            free(matrix);
            return 1;
        }
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = i * cols + j;
        }
    }

    int indices[] = {1, 4, 8, 15};
    int num_indices = sizeof(indices) / sizeof(indices[0]);
    int out_size = 0;

    int* extracted = extract_elements(matrix, rows, cols, indices, num_indices, &out_size);

    for (int i = 0; i < out_size; i++) {
        printf("%d ", extracted[i]);
    }
    printf("\n");

    if (extracted) free(extracted);

    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}