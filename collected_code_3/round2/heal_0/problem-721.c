#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 100

double findMaxAverage(int mat[MAX][MAX], int n) {
    double dp[MAX][MAX];
    dp[0][0] = mat[0][0];

    for (int i = 1; i < n; i++)
        dp[i][0] = dp[i-1][0] + mat[i][0];

    for (int j = 1; j < n; j++)
        dp[0][j] = dp[0][j-1] + mat[0][j];

    for (int i = 1; i < n; i++)
        for (int j = 1; j < n; j++)
            dp[i][j] = max(dp[i-1][j], dp[i][j-1]) + mat[i][j];

    return dp[n-1][n-1] / (2*n - 1);
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    int n;
    scanf("%d", &n);
    int mat[MAX][MAX];
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            scanf("%d", &mat[i][j]);

    printf("Maximum average of all paths is %f\n", findMaxAverage(mat, n));
    return 0;
}