#include <stdio.h>
#include <limits.h>

#define ROW 3
#define COL 3

int min(int x, int y, int z) {
    if (x < y) 
        return (x < z) ? x : z; 
    else
        return (y < z) ? y : z; 
}

int minCostPath(int cost[ROW][COL], int m, int n) {
    int dp[m+1][n+1];
    
    for (int i = 0; i <= m; i++) {
        dp[i][0] = INT_MAX;
    }
    for (int j = 0; j <= n; j++) {
        dp[0][j] = INT_MAX;
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
            dp[i][j] = cost[i][j] + min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1]);
        }
    }
    
    return dp[m][n];
}

int main() {
    int cost[ROW][COL] = {{1, 3, 1}, {1, 5, 1}, {4, 2, 1}};
    printf("Minimum Cost: %d\n", minCostPath(cost, ROW - 1, COL - 1));
    return 0;
}