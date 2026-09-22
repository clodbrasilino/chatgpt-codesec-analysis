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

    int val = 1;
    int top = 0, bottom = n - 1, left = 0, right = n - 1;

    while (top <= bottom && left <= right) {
        for (int i = left; i <= right; i++) {
            matrix[top][i] = val * val;
            val++;
        }
        top++;

        for (int i = top; i <= bottom; i++) {
            matrix[i][right] = val * val;
            val++;
        }
        right--;

        if (top <= bottom) {
            for (int i = right; i >= left; i--) {
                matrix[bottom][i] = val * val;
                val++;
            }
            bottom--;
        }

        if (left <= right) {
            for (int i = bottom; i >= top; i--) {
                matrix[i][left] = val * val;
                val++;
            }
            left++;
        }
    }

    return matrix;
}

void freeMatrix(int** matrix, int n) {
    if (matrix) {
        for (int i = 0; i < n; i++) {
            free(matrix[i]);
        }
        free(matrix);
    }
}

int main(void) {
    int n = 4;
    int** matrix = generateSpiralMatrix(n);

    if (matrix) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                printf("%d\t", matrix[i][j]);
            }
            printf("\n");
        }
        freeMatrix(matrix, n);
    } else {
        fprintf(stderr, "Memory allocation failed or invalid input.\n");
        return 1;
    }

    return 0;
}