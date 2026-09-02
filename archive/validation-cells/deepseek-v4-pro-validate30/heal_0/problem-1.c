#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minCostPath(int **cost, int m, int n) {
    if (m < 0 || n < 0) return 0;
    
    int **dp = (int **)malloc((m + 1) * sizeof(int *));
    if (dp == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    
    for (int i = 0; i <= m; i++) {
        dp[i] = (int *)malloc((n + 1) * sizeof(int));
        if (dp[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            for (int j = 0; j < i; j++) {
                free(dp[j]);
            }
            free(dp);
            exit(EXIT_FAILURE);
        }
    }
    
    dp[0][0] = cost[0][0];
    
    for (int i = 1; i <= m; i++) {
        dp[i][0] = dp[i-1][0] + cost[i][0];
    }
    
    for (int j = 1; j <= n; j++) {
        dp[0][j] = dp[0][j-1] + cost[0][j];
    }
    
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            int min_prev = dp[i-1][j];
            if (dp[i][j-1] < min_prev) {
                min_prev = dp[i][j-1];
            }
            if (dp[i-1][j-1] < min_prev) {
                min_prev = dp[i-1][j-1];
            }
            dp[i][j] = cost[i][j] + min_prev;
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
    int m = 2;
    int n = 2;
    
    int **cost = (int **)malloc((m + 1) * sizeof(int *));
    if (cost == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    for (int i = 0; i <= m; i++) {
        cost[i] = (int *)malloc((n + 1) * sizeof(int));
        if (cost[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            for (int j = 0; j < i; j++) {
                free(cost[j]);
            }
            free(cost);
            return EXIT_FAILURE;
        }
    }
    
    int temp[3][3] = {
        {1, 2, 3},
        {4, 8, 2},
        {1, 5, 3}
    };
    
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            cost[i][j] = temp[i][j];
        }
    }
    
    int result = minCostPath(cost, m, n);
    printf("Minimum cost path from (0,0) to (%d,%d): %d\n", m, n, result);
    
    for (int i = 0; i <= m; i++) {
        free(cost[i]);
    }
    free(cost);
    
    return 0;
}