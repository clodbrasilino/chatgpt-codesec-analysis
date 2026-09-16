#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  expected 'int (*)[n]' but argument is of type 'int **'
 */
void fillSpiralMatrix(int n, int matrix[n][n]) {
    int value = 1;
    int layer = 0;
    while (value <= n * n) {
        for (int i = layer; i < n - layer; i++) {
            matrix[layer][i] = value++;
        }
        for (int i = layer + 1; i < n - layer; i++) {
            matrix[i][n - layer - 1] = value++;
        }
        for (int i = n - layer - 2; i >= layer; i--) {
            matrix[n - layer - 1][i] = value++;
        }
        for (int i = n - layer - 2; i > layer; i--) {
            matrix[i][layer] = value++;
        }
        layer++;
    }
}

int main() {
    int n;
    printf("Enter the size of the matrix: ");
    scanf("%d", &n);

    if (n <= 0) {
        return 1;
    }

    int **matrix = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int *)malloc(n * sizeof(int));
    }

    /* Possible weaknesses found:
     *  passing argument 2 of 'fillSpiralMatrix' from incompatible pointer type [-Wincompatible-pointer-types]
     */
    fillSpiralMatrix(n, matrix);

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

    return 0;
}