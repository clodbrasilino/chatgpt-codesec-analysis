#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#define MAX_N 100

double getMaxPathAverage(int matrix[MAX_N][MAX_N], int n) {
    double dp[n][n];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == 0 && j == 0) {
                dp[i][j] = matrix[i][j];
            } else if (i == 0) {
                dp[i][j] = dp[i][j - 1] + matrix[i][j];
            } else if (j == 0) {
                dp[i][j] = dp[i - 1][j] + matrix[i][j];
            } else {
                dp[i][j] = fmax(dp[i - 1][j], dp[i][j - 1]) + matrix[i][j];
            }
        }
    }
    return dp[n - 1][n - 1] / (2 * n - 1);
}

int main() {
    int n;
    printf("Enter the size of the matrix: ");
    scanf("%d", &n);
    
    if (n <= 0 || n > MAX_N) {
        fprintf(stderr, "Invalid size!\n");
        return 1;
    }

    int matrix[MAX_N][MAX_N];
    printf("Enter the elements of the matrix:\n");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%d", &matrix[i][j]);
        }
    }

    double maxAvg = getMaxPathAverage(matrix, n);
    printf("Maximum average: %.2f\n", maxAvg);

    return 0;
}