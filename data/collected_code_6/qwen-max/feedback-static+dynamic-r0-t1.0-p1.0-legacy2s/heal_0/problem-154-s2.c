#include <stdio.h>
#include <stdlib.h>

int** createMatrix(int rows, int cols) {
    int **matrix = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int *)malloc(cols * sizeof(int));
    }
    return matrix;
}

void freeMatrix(int **matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int* extractElements(int **matrix, int rows, int cols, int step, int *outSize) {
    *outSize = (rows * cols + step - 1) / step;
    int *result = (int *)malloc(*outSize * sizeof(int));
    if (!result) {
        return NULL;
    }

    int k = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if ((i * cols + j) % step == 0) {
                result[k++] = matrix[i][j];
            }
        }
    }
    return result;
}

int main() {
    int rows = 4;
    int cols = 4;
    int step = 2;
    int outSize;

    int **matrix = createMatrix(rows, cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = i * cols + j + 1;
        }
    }

    int *result = extractElements(matrix, rows, cols, step, &outSize);

    if (result) {
        for (int i = 0; i < outSize; i++) {
            printf("%d ", result[i]);
        }
        free(result);
    }

    freeMatrix(matrix, rows);
    return 0;
}