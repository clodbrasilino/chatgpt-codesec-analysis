#include <stdio.h>
#include <stdlib.h>
#include <float.h>

double max(double a, double b) {
    return (a > b) ? a : b;
}

double findMaxAveragePath(int** matrix, int n) {
    double dp[n][n];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            dp[i][j] = -DBL_MAX;
        }
    }
    dp[0][0] = (double)matrix[0][0];

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i > 0) {
                dp[i][j] = max(dp[i][j], dp[i-1][j] + (double)matrix[i][j]);
            }
            if (j > 0) {
                dp[i][j] = max(dp[i][j], dp[i][j-1] + (double)matrix[i][j]);
            }
        }
    }

    double maxSum = dp[n-1][n-1];
    double maxAverage = maxSum / (2 * n - 1);
    return maxAverage;
}

int main() {
    int n;
    printf("Enter the size of the matrix: ");
    scanf("%d", &n);

    int** matrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; ++i) {
        matrix[i] = (int*)malloc(n * sizeof(int));
    }

    printf("Enter the elements of the matrix:\n");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%d", &matrix[i][j]);
        }
    }

    double maxAverage = findMaxAveragePath(matrix, n);
    printf("Maximum average path: %.2f\n", maxAverage);

    for (int i = 0; i < n; ++i) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}