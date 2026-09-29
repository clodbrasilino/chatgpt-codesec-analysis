#include <stdio.h>
#include <stdlib.h>

double maxAveragePath(int **matrix, int n) {
    double dp[n][n];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == 0 && j == 0) {
                dp[i][j] = matrix[0][0];
            } else if (i == 0) {
                dp[i][j] = dp[i][j-1] + matrix[i][j];
            } else if (j == 0) {
                dp[i][j] = dp[i-1][j] + matrix[i][j];
            } else {
                double left = dp[i][j-1] + matrix[i][j];
                double up = dp[i-1][j] + matrix[i][j];
                dp[i][j] = (left > up) ? left : up;
            }
            dp[i][j] /= (i + j + 1);
        }
    }
    double maxAvg = dp[0][0];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
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