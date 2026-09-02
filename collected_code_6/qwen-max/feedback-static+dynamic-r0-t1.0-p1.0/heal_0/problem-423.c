#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int goldMineSolver(int **mine, int n, int m, int i, int j, int **dp) {
    if (i < 0 || i >= n || j < 0 || j >= m) {
        return 0;
    }
    if (j == m-1) {
        dp[i][j] = mine[i][j];
        return dp[i][j];
    }
    if (dp[i][j] != -1) {
        return dp[i][j];
    }
    
    int right_top = goldMineSolver(mine, n, m, i-1, j+1, dp);
    int right = goldMineSolver(mine, n, m, i, j+1, dp);
    int right_bottom = goldMineSolver(mine, n, m, i+1, j+1, dp);
    
    dp[i][j] = mine[i][j] + max(right_top, max(right, right_bottom));
    
    return dp[i][j];
}

int solveGoldMine(int **mine, int n, int m) {
    int **dp = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; ++i) {
        dp[i] = (int *)calloc(m, sizeof(int));
    }

    int maxGold = 0;
    for (int i = 0; i < n; ++i) {
        dp[i][0] = -1;
    }
    for (int i = 0; i < n; ++i) {
        maxGold = max(maxGold, goldMineSolver(mine, n, m, i, 0, dp));
    }

    for (int i = 0; i < n; ++i) {
        free(dp[i]);
    }
    free(dp);
    
    return maxGold;
}

int main() {
    int n = 4;
    int m = 4;
    int **mine = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; ++i) {
        mine[i] = (int *)malloc(m * sizeof(int));
    }

    mine[0][0] = 1; mine[0][1] = 3; mine[0][2] = 1; mine[0][3] = 5;
    mine[1][0] = 2; mine[1][1] = 2; mine[1][2] = 4; mine[1][3] = 1;
    mine[2][0] = 5; mine[2][1] = 0; mine[2][2] = 2; mine[2][3] = 3;
    mine[3][0] = 0; mine[3][1] = 6; mine[3][2] = 1; mine[3][3] = 2;

    int result = solveGoldMine(mine, n, m);
    printf("Maximum gold: %d\n", result);

    for (int i = 0; i < n; ++i) {
        free(mine[i]);
    }
    free(mine);
    
    return 0;
}