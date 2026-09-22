#include <stdio.h>
#include <stdlib.h>

void fillMatrixSpiral(int n, int **matrix) {
    int value = 1;
    int top = 0, down = n - 1, left = 0, right = n - 1;

    while (top <= down && left <= right) {
        for (int i = left; i <= right; ++i)
            matrix[top][i] = value++;
        top++;

        for (int i = top; i <= down; ++i)
            matrix[i][right] = value++;
        right--;

        if (top <= down) {
            for (int i = right; i >= left; --i)
                matrix[down][i] = value++;
            down--;
        }

        if (left <= right) {
            for (int i = down; i >= top; --i)
                matrix[i][left] = value++;
            left++;
        }
    }
}

int **createMatrix(int n) {
    int **matrix = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int *)malloc(n * sizeof(int));
    }
    return matrix;
}

void freeMatrix(int **matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main() {
    int n = 3;
    int **matrix = createMatrix(n);

    fillMatrixSpiral(n, matrix);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    freeMatrix(matrix, n);
    return 0;
}