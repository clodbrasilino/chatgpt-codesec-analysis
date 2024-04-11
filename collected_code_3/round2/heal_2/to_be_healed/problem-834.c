#include <stdio.h>
#include <stdlib.h>

void generateSpiralMatrix(int n) {
    int **matrix = (int **)malloc(n * sizeof(int *));
    if (matrix == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    for (int i = 0; i < n; i++) {
        matrix[i] = (int *)malloc(n * sizeof(int));
        if (matrix[i] == NULL) {
            printf("Memory allocation failed.\n");
            exit(1);
        }
    }

    int value = 1;
    int rowStart = 0, rowEnd = n - 1;
    int colStart = 0, colEnd = n - 1;

    while (value <= n * n) {
        for (int i = colStart; i <= colEnd; i++) {
            /* Possible weaknesses found:
             *  use of uninitialized value '*matrix_87 + _15' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
             */
            matrix[rowStart][i] = value++;
        }
        rowStart++;

        for (int i = rowStart; i <= rowEnd; i++) {
            matrix[i][colEnd] = value++;
        }
        colEnd--;

        for (int i = colEnd; i >= colStart; i--) {
            matrix[rowEnd][i] = value++;
        }
        rowEnd--;

        for (int i = rowEnd; i >= rowStart; i--) {
            matrix[i][colStart] = value++;
        }
        colStart++;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            /* Possible weaknesses found:
             *  use of uninitialized value '*_49 + _51' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
             */
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
    int n;
    printf("Enter the value of n: ");
    scanf("%d", &n);
    generateSpiralMatrix(n);
    return 0;
}