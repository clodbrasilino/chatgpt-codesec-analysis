#include <stdio.h>
#include <stdlib.h>

void fillMatrixInSpiralOrder(int n, int **matrix) {
    int num = 1, layer;
    int startRow = 0, endRow = n - 1;
    int startCol = 0, endCol = n - 1;

    while (startRow <= endRow && startCol <= endCol) {
        for (layer = startCol; layer <= endCol; layer++) {
            matrix[startRow][layer] = num++;
        }
        startRow++;
        for (layer = startRow; layer <= endRow; layer++) {
            matrix[layer][endCol] = num++;
        }
        endCol--;
        if (startRow <= endRow) {
            for (layer = endCol; layer >= startCol; layer--) {
                matrix[endRow][layer] = num++;
            }
            endRow--;
        }
        if (startCol <= endCol) {
            for (layer = endRow; layer >= startRow; layer--) {
                matrix[layer][startCol] = num++;
            }
            startCol++;
        }
    }
}

int main() {
    int n;
    printf("Enter the size of the matrix: ");
    scanf("%d", &n);

    int **matrix = (int **)malloc(n * sizeof(int *));
    if (!matrix) {
        return 1;
    }

    for (int i = 0; i < n; i++) {
        matrix[i] = (int *)malloc(n * sizeof(int));
        if (!matrix[i]) {
            for (int j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            return 1;
        }
    }

    fillMatrixInSpiralOrder(n, matrix);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%4d", matrix[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}