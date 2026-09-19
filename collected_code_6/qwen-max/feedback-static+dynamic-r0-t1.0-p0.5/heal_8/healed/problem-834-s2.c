#include <stdio.h>
#include <stdlib.h>

void fillSpiralMatrix(int n, int matrix[n][n]) {
    int val = 1;
    int layer = 0;
    while (layer < n / 2) {
        for (int i = layer; i < n - layer; ++i) {
            matrix[layer][i] = val++;
        }
        for (int i = layer + 1; i < n - layer; ++i) {
            matrix[i][n - layer - 1] = val++;
        }
        for (int i = n - layer - 2; i >= layer; --i) {
            matrix[n - layer - 1][i] = val++;
        }
        for (int i = n - layer - 2; i > layer; --i) {
            matrix[i][layer] = val++;
        }
        layer++;
    }
    if (n % 2 != 0) {
        matrix[n / 2][n / 2] = val;
    }
}

int main() {
    int n;
    printf("Enter the size of the matrix: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        return 1;
    }

    int **matrix = malloc(n * sizeof(int *));
    for (int i = 0; i < n; ++i) {
        matrix[i] = malloc(n * sizeof(int));
    }

    fillSpiralMatrix(n, matrix);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%4d", matrix[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < n; ++i) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}