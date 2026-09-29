#include <stdio.h>
#include <stdlib.h>

int getMaxGold(int **mine, int m, int n) {
    if (m <= 0 || n <= 0) {
        return 0;
    }

    int **dp = (int **)malloc(m * sizeof(int *));
    if (dp == NULL) {
        return 0;
    }

    for (int i = 0; i < m; i++) {
        dp[i] = (int *)malloc(n * sizeof(int));
        if (dp[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(dp[j]);
            }
            free(dp);
            return 0;
        }
    }

    for (int i = 0; i < m; i++) {
        dp[i][n - 1] = mine[i][n - 1];
    }

    for (int col = n - 2; col >= 0; col--) {
        for (int row = 0; row < m; row++) {
            int right = dp[row][col + 1];
            int right_up = (row == 0) ? 0 : dp[row - 1][col + 1];
            int right_down = (row == m - 1) ? 0 : dp[row + 1][col + 1];
            dp[row][col] = mine[row][col] + (right > right_up ? (right > right_down ? right : right_down) : (right_up > right_down ? right_up : right_down));
        }
    }

    int max_gold = dp[0][0];
    for (int i = 1; i < m; i++) {
        if (dp[i][0] > max_gold) {
            max_gold = dp[i][0];
        }
    }

    for (int i = 0; i < m; i++) {
        free(dp[i]);
    }
    free(dp);

    return max_gold;
}

int main() {
    int m = 4;
    int n = 4;

    int **mine = (int **)malloc(m * sizeof(int *));
    if (mine == NULL) {
        return 1;
    }

    for (int i = 0; i < m; i++) {
        mine[i] = (int *)malloc(n * sizeof(int));
        if (mine[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(mine[j]);
            }
            free(mine);
            return 1;
        }
    }

    int values[4][4] = {
        {1, 3, 1, 5},
        {2, 2, 4, 1},
        {5, 0, 2, 3},
        {0, 6, 1, 2}
    };

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            mine[i][j] = values[i][j];
        }
    }

    int result = getMaxGold(mine, m, n);
    printf("%d\n", result);

    for (int i = 0; i < m; i++) {
        free(mine[i]);
    }
    free(mine);

    return 0;
}