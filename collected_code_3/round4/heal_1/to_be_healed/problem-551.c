#include <stdio.h>
#include <stdlib.h>

int** extractColumn(int** matrix, int matrixSize, int* matrixColSize, int col, int* returnSize) {
    *returnSize = matrixSize;
    int** column = (int**)malloc((*returnSize) * sizeof(int*));
    for (int i = 0; i < matrixSize; i++) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'column' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        column[i] = (int*)malloc(sizeof(int));
        /* Possible weaknesses found:
         *  dereference of possibly-NULL '*column_27 + _16' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        *column[i] = matrix[i][col];
    }
    return column;
}

int main() {
    int matrixSize = 3;
    int matrixColSize[3] = {3, 3, 3};
    int** matrix = (int**)malloc(matrixSize * sizeof(int*));
    for (int i = 0; i < matrixSize; i++) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'matrix' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        matrix[i] = (int*)malloc(matrixColSize[i] * sizeof(int));
        for (int j = 0; j < matrixColSize[i]; j++) {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL '*matrix_51 + _12 + (long unsigned int)j * 4' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            matrix[i][j] = i * matrixSize + j;
        }
    }
    int returnSize;
    int** column = extractColumn(matrix, matrixSize, matrixColSize, 1, &returnSize);
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