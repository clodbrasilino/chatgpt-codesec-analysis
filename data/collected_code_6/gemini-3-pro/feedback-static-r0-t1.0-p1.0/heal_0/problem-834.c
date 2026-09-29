#include <stdio.h>
#include <stdlib.h>

int** generateSpiralMatrix(int n) {
    if (n <= 0) {
        return NULL;
    }

    int** matrix = (int**)malloc(n * sizeof(int*));
    if (!matrix) {
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        matrix[i] = (int*)malloc(n * sizeof(int));
        if (!matrix[i]) {
            for (int j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            return NULL;
        }
    }

    int top = 0, bottom = n - 1, left = 0, right = n - 1;
    int num = 1;

    while (top <= bottom && left <= right) {
        for (int i = left; i <= right; i++) {
            matrix[top][i] = num * num;
            num++;
        }
        top++;

        for (int i = top; i <= bottom; i++) {
            matrix[i][right] = num * num;
            num++;
        }
        right--;

        if (top <= bottom) {
            for (int i = right; i >= left; i--) {
                matrix[bottom][i] = num * num;
                num++;
            }
            bottom--;
        }

        if (left <= right) {
            for (int i = bottom; i >= top; i--) {
                matrix[i][left] = num * num;
                num++;
            }
            left++;
        }
    }

    return matrix;
}

void printAndFreeMatrix(int** matrix, int n) {
    if (!matrix) {
        return;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main() {
    int n = 4;
    int** spiralMatrix = generateSpiralMatrix(n);
    if (spiralMatrix) {
        printAndFreeMatrix(spiralMatrix, n);
    } else {
        printf("Failed to generate matrix.\n");
    }
    return 0;
}