#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int gold_mine(int **gold, int n, int m, int *result) {
    if (gold == NULL || result == NULL || n <= 0 || m <= 0) {
        return -1;
    }

    int **dp = (int **)malloc((size_t)n * sizeof(int *));
    if (dp == NULL) {
        return -1;
    }

    for (int i = 0; i < n; i++) {
        dp[i] = (int *)malloc((size_t)m * sizeof(int));
        if (dp[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(dp[j]);
            }
            free(dp);
            return -1;
        }
    }

    for (int i = 0; i < n; i++) {
        dp[i][m - 1] = gold[i][m - 1];
    }

    for (int col = m - 2; col >= 0; col--) {
        for (int row = 0; row < n; row++) {
            int right = dp[row][col + 1];
            int right_up = (row > 0) ? dp[row - 1][col + 1] : 0;
            int right_down = (row < n - 1) ? dp[row + 1][col + 1] : 0;
            dp[row][col] = gold[row][col] + max(right, max(right_up, right_down));
        }
    }

    *result = dp[0][0];
    for (int i = 1; i < n; i++) {
        *result = max(*result, dp[i][0]);
    }

    for (int i = 0; i < n; i++) {
        free(dp[i]);
    }
    free(dp);

    return 0;
}

int main(void) {
    int n = 4, m = 4;
    int raw_gold[4][4] = {
        {1, 3, 1, 5},
        {2, 2, 4, 1},
        {5, 0, 2, 3},
        {0, 6, 1, 2}
    };

    int **gold = (int **)malloc((size_t)n * sizeof(int *));
    if (gold == NULL) {
        return 1;
    }

    for (int i = 0; i < n; i++) {
        gold[i] = (int *)malloc((size_t)m * sizeof(int));
        if (gold[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(gold[j]);
            }
            free(gold);
            return 1;
        }
        for (int j = 0; j < m; j++) {
            gold[i][j] = raw_gold[i][j];
        }
    }

    int result = 0;
    int ret = gold_mine(gold, n, m, &result);
    if (ret != 0) {
        for (int i = 0; i < n; i++) {
            free(gold[i]);
        }
        free(gold);
        return 1;
    }

    printf("Maximum gold: %d\n", result);

    for (int i = 0; i < n; i++) {
        free(gold[i]);
    }
    free(gold);

    return 0;
}