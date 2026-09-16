#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int goldmine(int gold[][5], int m, int n) {
    int dp[m][n];
    for (int col = n-1; col >= 0; --col) {
        for (int row = 0; row < m; ++row) {
            if (col == n-1) {
                dp[row][col] = gold[row][col];
            } else if (row == 0) {
                dp[row][col] = gold[row][col] + max(dp[row][col+1], dp[row+1][col+1]);
            } else if (row == m-1) {
                dp[row][col] = gold[row][col] + max(dp[row][col+1], dp[row-1][col+1]);
            } else {
                dp[row][col] = gold[row][col] + max(max(dp[row-1][col+1], dp[row+1][col+1]), dp[row][col+1]);
            }
        }
    }
    int res = dp[0][0];
    for (int i = 1; i < m; ++i) {
        res = max(res, dp[i][0]);
    }
    return res;
}

int main() {
    int gold[4][5] = {
        {1, 3, 1, 5, 8},
        {2, 2, 4, 1, 5},
        {5, 0, 2, 3, 4},
        {0, 6, 1, 2, 3}
    };
    int m = 4, n = 5;
    printf("Maximum gold: %d\n", goldmine(gold, m, n));
    return 0;
}