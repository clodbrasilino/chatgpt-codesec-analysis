#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 100

double findMaxAverage(int matrix[MAX][MAX], int n) {
    double dp[MAX][MAX];
    dp[0][0] = matrix[0][0];

    for (int i = 1; i < n; i++) {
        dp[i][0] = dp[i - 1][0] + matrix[i][0];
        dp[0][i] = dp[0][i - 1] + matrix[0][i];
    }

    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            /* Possible weaknesses found:
             *  implicit declaration of function 'max' [-Wimplicit-function-declaration]
             */
            dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]) + matrix[i][j];
        }
    }

    return dp[n - 1][n - 1] / (2 * n - 1);
}

int main() {
    int n;
    scanf("%d", &n);
    int matrix[MAX][MAX];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
    printf("%.2f\n", findMaxAverage(matrix, n));
    return 0;
}