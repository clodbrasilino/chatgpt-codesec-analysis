#include <stdio.h>
#include <stdlib.h>

int* extract_elements(int** matrix, int rows, int cols, int extract_col, int* out_size) {
    if (matrix == NULL || out_size == NULL || rows <= 0 || cols <= 0 || extract_col < 0 || extract_col >= cols) {
        if (out_size != NULL) {
            *out_size = 0;
        }
        return NULL;
    }

    int* extracted = (int*)malloc(rows * sizeof(int));
    if (extracted == NULL) {
        *out_size = 0;
        return NULL;
    }

    for (int i = 0; i < rows; i++) {
        if (matrix[i] == NULL) {
            free(extracted);
            *out_size = 0;
            return NULL;
        }
        extracted[i] = matrix[i][extract_col];
    }

    *out_size = rows;
    return extracted;
}

int main(void) {
    int rows = 3;
    int cols = 3;
    int extract_col = 1;

    int** matrix = (int**)malloc(rows * sizeof(int*));
    if (matrix == NULL) {
        return 1;
    }

    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
        if (matrix[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            return 1;
        }
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = i * cols + j;
        }
    }

    int out_size = 0;
    int* extracted = extract_elements(matrix, rows, cols, extract_col, &out_size);

    if (extracted != NULL) {
        for (int i = 0; i < out_size; i++) {
            printf("%d ", extracted[i]);
        }
        printf("\n");
        free(extracted);
    }

    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}