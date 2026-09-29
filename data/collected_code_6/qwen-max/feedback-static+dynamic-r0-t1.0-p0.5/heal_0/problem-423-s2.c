#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int goldMine(int **gold, int m, int n) {
    int **dp = (int **)malloc(m * sizeof(int *));
    for (int i = 0; i < m; ++i) {
        dp[i] = (int *)calloc(n, sizeof(int));
    }

    for (int col = n - 1; col >= 0; --col) {
        for (int row = 0; row < m; ++row) {
            int right = (col == n - 1) ? 0 : dp[row][col + 1];
            int right_up = (row == 0 || col == n - 1) ? 0 : dp[row - 1][col + 1];
            int right_down = (row == m - 1 || col == n - 1) ? 0 : dp[row + 1][col + 1];

            dp[row][col] = gold[row][col] + max(right, max(right_up, right_down));
        }
    }

    int max_gold = 0;
    for (int i = 0; i < m; ++i) {
        if (dp[i][0] > max_gold) {
            max_gold = dp[i][0];
        }
    }

    for (int i = 0; i < m; ++i) {
        free(dp[i]);
    }
    free(dp);

    return max_gold;
}

int main() {
    int m = 3, n = 3;
    int **gold = (int **)malloc(m * sizeof(int *));
    for (int i = 0; i < m; ++i) {
        gold[i] = (int *)malloc(n * sizeof(int));
    }

    gold[0][0] = 1; gold[0][1] = 3; gold[0][2] = 3;
    gold[1][0] = 2; gold[1][1] = 1; gold[1][2] = 4;
    gold[2][0] = 0; gold[2][1] = 6; gold[2][2] = 4;

    int result = goldMine(gold, m, n);
    printf("Maximum gold: %d\n", result);

    for (int i = 0; i < m; ++i) {
        free(gold[i]);
    }
    free(gold);

    return 0;
}