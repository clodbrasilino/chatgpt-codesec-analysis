#include <stdio.h>
#include <stdlib.h>

int min(int a, int b) {
    return (a < b) ? a : b;
}

int minCostPath(int **cost, int m, int n) {
    if (cost == NULL || m < 0 || n < 0) {
        return -1;
    }

    int **dp = (int **)malloc((m + 1) * sizeof(int *));
    if (dp == NULL) {
        return -1;
    }

    for (int i = 0; i <= m; i++) {
        dp[i] = (int *)malloc((n + 1) * sizeof(int));
        if (dp[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(dp[j]);
            }
            free(dp);
            return -1;
        }
    }

    dp[0][0] = cost[0][0];

    for (int i = 1; i <= m; i++) {
        dp[i][0] = dp[i - 1][0] + cost[i][0];
    }

    for (int j = 1; j <= n; j++) {
        dp[0][j] = dp[0][j - 1] + cost[0][j];
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            dp[i][j] = cost[i][j] + min(dp[i - 1][j - 1], min(dp[i - 1][j], dp[i][j - 1]));
        }
    }

    int result = dp[m][n];

    for (int i = 0; i <= m; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}

int main() {
    int m = 2;
    int n = 2;

    int **cost = (int **)malloc((m + 1) * sizeof(int *));
    if (cost == NULL) {
        return 1;
    }

    int row0[] = {1, 2, 3};
    int row1[] = {4, 8, 2};
    int row2[] = {1, 5, 3};

    cost[0] = row0;
    cost[1] = row1;
    cost[2] = row2;

    int result = minCostPath(cost, m, n);

    if (result != -1) {
        printf("%d\n", result);
    }

    free(cost);

    return 0;
}