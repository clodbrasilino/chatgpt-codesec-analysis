#include <stdio.h>

#define MAX_ROWS 100
#define MAX_COLS 100

int max(int a, int b) {
    return (a > b) ? a : b;
}

int getMaxGold(int mines[MAX_ROWS][MAX_COLS], int m, int n) {
    int dp[MAX_ROWS][MAX_COLS] = {0};
    
    for (int col = n - 1; col >= 0; col--) {
        for (int row = 0; row < m; row++) {
            int right = (col == n - 1) ? 0 : dp[row][col + 1];
            int right_up = (col == n - 1 || row == 0) ? 0 : dp[row - 1][col + 1];
            int right_down = (col == n - 1 || row == m - 1) ? 0 : dp[row + 1][col + 1];
            
            dp[row][col] = mines[row][col] + max(right, max(right_up, right_down));
        }
    }

    int maxGold = dp[0][0];

    for (int i = 1; i < m; i++) {
        maxGold = max(maxGold, dp[i][0]);
    }
    
    return maxGold;
}

int main() {
    int mines[MAX_ROWS][MAX_COLS] = {
        {1, 3, 1, 5},
        {2, 2, 4, 1},
        {5, 0, 2, 3},
        {0, 6, 1, 2}
    };
    
    int m = sizeof(mines) / sizeof(mines[0]);
    int n = sizeof(mines[0]) / sizeof(mines[0][0]);
  
    int maxGold = getMaxGold(mines, m, n);
    printf("Maximum amount of gold that can be collected: %d\n", maxGold);

    return 0;
}