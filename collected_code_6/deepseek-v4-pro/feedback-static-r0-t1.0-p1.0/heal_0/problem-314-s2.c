#include <stdio.h>
#include <stdlib.h>

int max_sum_2xn(int grid[2][100], int n) {
    if (n <= 0) return 0;
    
    int dp[n];
    
    dp[0] = (grid[0][0] > grid[1][0]) ? grid[0][0] : grid[1][0];
    
    if (n == 1) return dp[0];
    
    int max_val = (grid[0][1] > grid[1][1]) ? grid[0][1] : grid[1][1];
    dp[1] = (dp[0] > max_val) ? dp[0] : max_val;
    
    for (int i = 2; i < n; i++) {
        int current_max = (grid[0][i] > grid[1][i]) ? grid[0][i] : grid[1][i];
        int include_current = dp[i-2] + current_max;
        dp[i] = (include_current > dp[i-1]) ? include_current : dp[i-1];
    }
    
    return dp[n-1];
}

int main(void) {
    int n;
    int grid[2][100];
    
    printf("Enter number of columns: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (n <= 0 || n > 100) {
        fprintf(stderr, "Invalid number of columns\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter the grid values (2 rows, %d columns):\n", n);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < n; j++) {
            if (scanf("%d", &grid[i][j]) != 1) {
                fprintf(stderr, "Invalid input\n");
                return EXIT_FAILURE;
            }
        }
    }
    
    int result = max_sum_2xn(grid, n);
    printf("Maximum sum: %d\n", result);
    
    return EXIT_SUCCESS;
}