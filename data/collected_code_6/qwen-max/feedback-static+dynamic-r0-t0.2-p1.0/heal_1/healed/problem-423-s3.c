#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int goldMine(int (*gold)[4], int m, int n) {
    int dp[m][n];
    for (int col = n-1; col >= 0; --col) {
        for (int row = 0; row < m; ++row) {
            int right = (col == n-1) ? 0 : dp[row][col+1];
            int right_up = (row == 0 || col == n-1) ? 0 : dp[row-1][col+1];
            int right_down = (row == m-1 || col == n-1) ? 0 : dp[row+1][col+1];
            dp[row][col] = gold[row][col] + max(right, max(right_up, right_down));
        }
    }
    int max_gold = 0;
    for (int i = 0; i < m; ++i) {
        if (dp[i][0] > max_gold) {
            max_gold = dp[i][0];
        }
    }
    return max_gold;
}

int main() {
    int gold[4][4] = {
        {1, 3, 3, 2},
        {2, 1, 4, 8},
        {0, 6, 4, 2},
        {6, 3, 3, 2}
    };
    int m = 4;
    int n = 4;
    printf("Maximum gold that can be collected: %d\n", goldMine(gold, m, n));
    return 0;
}