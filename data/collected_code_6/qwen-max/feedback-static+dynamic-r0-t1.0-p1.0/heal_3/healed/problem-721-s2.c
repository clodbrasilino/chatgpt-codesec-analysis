#include <stdio.h>
#include <stdlib.h>

double maxAveragePath(int **matrix, int n) {
    double dp[n][n], maxAvg = 0.0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == 0 && j == 0) {
                dp[i][j] = matrix[0][0];
            } else if (i == 0) {
                dp[i][j] = dp[i][j-1] * (j) / (j + 1) + matrix[i][j] / (j + 1);
            } else if (j == 0) {
                dp[i][j] = dp[i-1][j] * (i) / (i + 1) + matrix[i][j] / (i + 1);
            } else {
                dp[i][j] = (dp[i-1][j] * (i + j) > dp[i][j-1] * (i + j)) ? 
                    dp[i-1][j] * (i + j) / (i + j + 1) + matrix[i][j] / (i + j + 1) : 
                    dp[i][j-1] * (i + j) / (i + j + 1) + matrix[i][j] / (i + j + 1);
            }
            if (dp[i][j] > maxAvg) {
                maxAvg = dp[i][j];
            }
        }
    }
    return maxAvg;
}

int main() {
    int n;
    printf("Enter the size of the matrix: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Size must be positive.\n");
        return 1;
    }

    int **matrix = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; ++i) {
        matrix[i] = (int *)malloc(n * sizeof(int));
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%d", &matrix[i][j]);
        }
    }

    double result = maxAveragePath(matrix, n);
    printf("Maximum average path: %.2f\n", result);

    for (int i = 0; i < n; ++i) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}