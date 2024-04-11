#include <stdio.h>
#include <stdlib.h>

int** extractColumn(int** matrix, int matrixSize, int* matrixColSize, int col, int* returnSize) {
    *returnSize = matrixSize;
    int** column = (int**)malloc(*returnSize * sizeof(int*));

    if (!column) {
        return NULL;
    }

    for (int i = 0; i < matrixSize; i++) {
        if (col >= matrixColSize[i]){
            while(i--){
                free(column[i]);
            }
            free(column);
            return NULL;
        }

        column[i] = (int*)malloc(sizeof(int));

        if (!column[i]) {
            while(i--) {
                free(column[i]);
            }
            free(column);
            return NULL;
        }

        /* Possible weaknesses found:
         *  use of uninitialized value '*_29 + _31' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
         */
        *column[i] = matrix[i][col];
    }
    return column;
}

int main() {
    int matrixSize = 3;
    int matrixColSize[3] = {3, 3, 3};

    int** matrix = (int**)malloc(matrixSize * sizeof(int*));

    if (!matrix) {
        return -1;
    }

    for (int i = 0; i < matrixSize; i++) {
        matrix[i] = (int*)malloc(matrixColSize[i] * sizeof(int));

        if (!matrix[i]) {
            while(i--) {
                free(matrix[i]);
            }
            free(matrix);
            return -1;
        }

        for (int j = 0; j < matrixColSize[i]; j++) {
            matrix[i][j] = i * matrixSize + j;
        }
    }

    int returnSize;

    int** column = extractColumn(matrix, matrixSize, matrixColSize, 1, &returnSize);

    if (!column) {
        for (int i = 0; i < matrixSize; i++) {
            free(matrix[i]);
        }
        free(matrix);
        return -1;
    }

    for (int i = 0; i < returnSize; i++) {
        printf("%d ", *column[i]);
    }

    for (int i = 0; i < matrixSize; i++) {
        free(matrix[i]);
    }
    free(matrix);

    for (int i = 0; i < returnSize; i++) {
        free(column[i]);
    }
    free(column);

    return 0;
}