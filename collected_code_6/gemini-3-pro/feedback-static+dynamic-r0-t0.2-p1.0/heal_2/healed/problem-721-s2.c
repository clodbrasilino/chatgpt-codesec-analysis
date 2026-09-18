#include <stdio.h>
#include <stdlib.h>

double findMaxAveragePath(int** matrix, int n) {
    if (n <= 0 || matrix == NULL) {
        return 0.0;
    }

    double** dp = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) {
        dp[i] = (double*)malloc(n * sizeof(double));
    }

    dp[0][0] = matrix[0][0];

    for (int i = 1; i < n; i++) {
        dp[i][0] = dp[i - 1][0] + matrix[i][0];
    }

    for (int j = 1; j < n; j++) {
        dp[0][j] = dp[0][j - 1] + matrix[0][j];
    }

    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            if (dp[i - 1][j] > dp[i][j - 1]) {
                dp[i][j] = dp[i - 1][j] + matrix[i][j];
            } else {
                dp[i][j] = dp[i][j - 1] + matrix[i][j];
            }
        }
    }

    double maxAverage = dp[n - 1][n - 1] / (2.0 * n - 1.0);

    for (int i = 0; i < n; i++) {
        free(dp[i]);
    }
    free(dp);

    return maxAverage;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) {
        return 0;
    }

    int** matrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    double result = findMaxAveragePath(matrix, n);
    printf("%.1f\n", result);

    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}