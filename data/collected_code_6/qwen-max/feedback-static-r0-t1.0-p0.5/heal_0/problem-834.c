#include <stdio.h>
#include <stdlib.h>

void fillSpiralMatrix(int n, int matrix[n][n]) {
    int val = 1;
    int layer = 0;
    while (val <= n * n) {
        for (int i = layer; i < n - layer; ++i) {
            matrix[layer][i] = val++;
        }
        for (int i = layer + 1; i < n - layer; ++i) {
            matrix[i][n - layer - 1] = val++;
        }
        for (int i = n - layer - 2; i >= layer; --i) {
            if (layer < n - layer - 1) {
                matrix[n - layer - 1][i] = val++;
            }
        }
        for (int i = n - layer - 2; i > layer; --i) {
            if (layer < n - layer - 1) {
                matrix[i][layer] = val++;
            }
        }
        layer++;
    }
}

int main() {
    int n;
    printf("Enter the size of the matrix: ");
    scanf("%d", &n);

    int **matrix = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; ++i) {
        matrix[i] = (int *)malloc(n * sizeof(int));
    }

    fillSpiralMatrix(n, (int (*)[n])matrix);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < n; ++i) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}