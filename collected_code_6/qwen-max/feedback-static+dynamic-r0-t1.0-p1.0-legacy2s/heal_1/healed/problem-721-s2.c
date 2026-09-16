#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

double findMaxPathAverage(const int *matrix, int n) {
    double dp[n][n];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == 0 && j == 0) {
                dp[i][j] = matrix[0];
            } else if (i == 0) {
                dp[i][j] = dp[i][j-1] + matrix[j];
            } else if (j == 0) {
                dp[i][j] = dp[i-1][j] + matrix[i*n];
            } else {
                dp[i][j] = fmax(dp[i-1][j], dp[i][j-1]) + matrix[i*n + j];
            }
        }
    }
    return dp[n-1][n-1] / (2 * n - 1);
}

int main() {
    int n;
    printf("Enter the size of the square matrix: ");
    scanf("%d", &n);

    if (n <= 0) {
        return 1;
    }

    const int *matrix = (const int *)malloc(n * n * sizeof(int));
    if (!matrix) {
        return 1;
    }

    printf("Enter the elements of the matrix:\n");
    for (int i = 0; i < n * n; ++i) {
        scanf("%d", &((int *)matrix)[i]);
    }

    double maxAvg = findMaxPathAverage(matrix, n);
    printf("Maximum average path: %.2f\n", maxAvg);

    free((void *)matrix);
    return 0;
}