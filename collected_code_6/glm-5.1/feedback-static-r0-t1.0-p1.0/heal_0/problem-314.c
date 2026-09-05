#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return a > b ? a : b;
}

int max_adjacent_sum(int **grid, int n) {
    if (n <= 0) {
        return 0;
    }
    if (n == 1) {
        return max(grid[0][0], grid[1][0]);
    }
    int *dp = (int *)malloc(n * sizeof(int));
    if (dp == NULL) {
        return -1;
    }
    dp[0] = max(grid[0][0], grid[1][0]);
    dp[1] = max(dp[0], max(grid[0][1], grid[1][1]));
    for (int i = 2; i < n; i++) {
        int current = max(grid[0][i], grid[1][i]);
        dp[i] = max(dp[i - 1], dp[i - 2] + current);
    }
    int result = dp[n - 1];
    free(dp);
    return result;
}

int main() {
    int n = 5;
    int **grid = (int **)malloc(2 * sizeof(int *));
    if (grid == NULL) {
        return 1;
    }
    grid[0] = (int *)malloc(n * sizeof(int));
    grid[1] = (int *)malloc(n * sizeof(int));
    if (grid[0] == NULL || grid[1] == NULL) {
        free(grid[0]);
        free(grid[1]);
        free(grid);
        return 1;
    }
    grid[0][0] = 1; grid[0][1] = 2; grid[0][2] = 3; grid[0][3] = 4; grid[0][4] = 5;
    grid[1][0] = 6; grid[1][1] = 7; grid[1][2] = 8; grid[1][3] = 9; grid[1][4] = 10;
    int result = max_adjacent_sum(grid, n);
    printf("%d\n", result);
    free(grid[0]);
    free(grid[1]);
    free(grid);
    return 0;
}