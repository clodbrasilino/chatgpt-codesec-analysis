#include <stdio.h>
#include <stdlib.h>

int max_sum_2xn(int grid[][2], int n) {
    if (n <= 0) return 0;
    if (n == 1) {
        int max_val = grid[0][0] > grid[0][1] ? grid[0][0] : grid[0][1];
        return max_val > 0 ? max_val : 0;
    }

    int *dp = (int *)malloc(n * sizeof(int));
    if (dp == NULL) return 0;

    int col_max_0 = grid[0][0] > grid[0][1] ? grid[0][0] : grid[0][1];
    int col_max_1 = grid[1][0] > grid[1][1] ? grid[1][0] : grid[1][1];

    dp[0] = col_max_0 > 0 ? col_max_0 : 0;
    int temp = col_max_1 > 0 ? col_max_1 : 0;
    dp[1] = dp[0] > temp ? dp[0] : temp;

    for (int i = 2; i < n; i++) {
        int col_max = grid[i][0] > grid[i][1] ? grid[i][0] : grid[i][1];
        if (col_max < 0) col_max = 0;
        int include_current = dp[i - 2] + col_max;
        dp[i] = dp[i - 1] > include_current ? dp[i - 1] : include_current;
    }

    int result = dp[n - 1];
    free(dp);
    return result;
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    int grid[100][2];
    for (int i = 0; i < n; i++) {
        if (scanf("%d %d", &grid[i][0], &grid[i][1]) != 2) {
            fprintf(stderr, "Invalid input\n");
            return 1;
        }
    }

    printf("%d\n", max_sum_2xn(grid, n));
    return 0;
}