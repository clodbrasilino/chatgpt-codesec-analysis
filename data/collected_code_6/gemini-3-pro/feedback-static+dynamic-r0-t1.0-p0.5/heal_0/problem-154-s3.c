#include <stdio.h>
#include <stdlib.h>

int* extract_elements(int** matrix, int rows, int cols, int target, int* out_count) {
    if (matrix == NULL || out_count == NULL || rows <= 0 || cols <= 0) {
        if (out_count != NULL) {
            *out_count = 0;
        }
        return NULL;
    }

    int count = 0;
    for (int i = 0; i < rows; i++) {
        if (matrix[i] == NULL) {
            *out_count = 0;
            return NULL;
        }
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] == target) {
                count++;
            }
        }
    }

    if (count == 0) {
        *out_count = 0;
        return NULL;
    }

    int* result = (int*)malloc(count * sizeof(int));
    if (result == NULL) {
        *out_count = 0;
        return NULL;
    }

    int index = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] == target) {
                result[index++] = matrix[i][j];
            }
        }
    }

    *out_count = count;
    return result;
}

int main(void) {
    int rows = 3;
    int cols = 3;
    int target = 5;

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
    }

    matrix[0][0] = 1; matrix[0][1] = 5; matrix[0][2] = 3;
    matrix[1][0] = 4; matrix[1][1] = 5; matrix[1][2] = 6;
    matrix[2][0] = 7; matrix[2][1] = 8; matrix[2][2] = 5;

    int out_count = 0;
    int* extracted = extract_elements(matrix, rows, cols, target, &out_count);

    if (extracted != NULL) {
        for (int i = 0; i < out_count; i++) {
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