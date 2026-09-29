#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

int minCostPath(int **cost, int m, int n) {
    if (cost == NULL || m < 0 || n < 0) {
        return INT_MIN;
    }
    
    int **dp = (int **)malloc((m + 1) * sizeof(int *));
    if (dp == NULL) {
        return INT_MIN;
    }
    
    for (int i = 0; i <= m; i++) {
        dp[i] = (int *)malloc((n + 1) * sizeof(int));
        if (dp[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(dp[j]);
            }
            free(dp);
            return INT_MIN;
        }
    }
    
    dp[0][0] = cost[0][0];
    
    for (int j = 1; j <= n; j++) {
        dp[0][j] = dp[0][j - 1] + cost[0][j];
    }
    
    for (int i = 1; i <= m; i++) {
        dp[i][0] = dp[i - 1][0] + cost[i][0];
    }
    
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            dp[i][j] = cost[i][j] + MIN(dp[i - 1][j], dp[i][j - 1]);
        }
    }
    
    int result = dp[m][n];
    
    for (int i = 0; i <= m; i++) {
        free(dp[i]);
    }
    free(dp);
    
    return result;
}

int main(void) {
    int m = 2, n = 2;
    int **cost = (int **)malloc((m + 1) * sizeof(int *));
    if (cost == NULL) {
        return 1;
    }
    
    int data[3][3] = {
        {1, 2, 3},
        {4, 8, 2},
        {1, 5, 3}
    };
    
    for (int i = 0; i <= m; i++) {
        cost[i] = (int *)malloc((n + 1) * sizeof(int));
        if (cost[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(cost[j]);
            }
            free(cost);
            return 1;
        }
        for (int j = 0; j <= n; j++) {
            cost[i][j] = data[i][j];
        }
    }
    
    int result = minCostPath(cost, m, n);
    if (result != INT_MIN) {
        printf("%d\n", result);
    }
    
    for (int i = 0; i <= m; i++) {
        free(cost[i]);
    }
    free(cost);
    
    return 0;
}