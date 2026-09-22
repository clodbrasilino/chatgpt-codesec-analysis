#include <stdio.h>
#include <stdlib.h>
#include <float.h>

double findMaxAveragePath(int n, int** matrix) {
    if (n <= 0 || matrix == NULL) {
        return 0.0;
    }

    double** dp = (double**)malloc(n * sizeof(double*));
    if (dp == NULL) {
        return 0.0;
    }
    for (int i = 0; i < n; i++) {
        dp[i] = (double*)malloc(n * sizeof(double));
        if (dp[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(dp[j]);
            }
            free(dp);
            return 0.0;
        }
    }

    dp[0][0] = matrix[0][0];

    for (int i = 1; i < n; i++) {
        dp[i][0] = dp[i-1][0] + matrix[i][0];
    }
    for (int j = 1; j < n; j++) {
        dp[0][j] = dp[0][j-1] + matrix[0][j];
    }

    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            if (dp[i-1][j] > dp[i][j-1]) {
                dp[i][j] = dp[i-1][j] + matrix[i][j];
            } else {
                dp[i][j] = dp[i][j-1] + matrix[i][j];
            }
        }
    }

    double maxPathSum = dp[n-1][n-1];
    double maxAverage = maxPathSum / (2 * n - 1);

    for (int i = 0; i < n; i++) {
        free(dp[i]);
    }
    free(dp);

    return maxAverage;
}

int main() {
    int n = 3;
    
    int** matrix = (int**)malloc(n * sizeof(int*));
    if (matrix == NULL) {
        return EXIT_FAILURE;
    }
    for (int i = 0; i < n; i++) {
        matrix[i] = (int*)malloc(n * sizeof(int));
        if (matrix[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            return EXIT_FAILURE;
        }
    }

    int values[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = values[i][j];
        }
    }

    double maxAvg = findMaxAveragePath(n, matrix);
    printf("Max average path: %f\n", maxAvg);

    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return EXIT_SUCCESS;
}