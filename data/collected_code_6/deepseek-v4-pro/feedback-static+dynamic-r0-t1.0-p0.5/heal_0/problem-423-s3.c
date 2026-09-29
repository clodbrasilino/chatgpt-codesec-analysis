#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int maxGold(int n, int m, int **mine) {
    if (n <= 0 || m <= 0 || mine == NULL) {
        return 0;
    }

    int **dp = (int **)malloc(n * sizeof(int *));
    if (dp == NULL) {
        return 0;
    }

    for (int i = 0; i < n; i++) {
        dp[i] = (int *)malloc(m * sizeof(int));
        if (dp[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(dp[j]);
            }
            free(dp);
            return 0;
        }
    }

    for (int col = m - 1; col >= 0; col--) {
        for (int row = 0; row < n; row++) {
            int right = (col == m - 1) ? 0 : dp[row][col + 1];
            int right_up = (row == 0 || col == m - 1) ? 0 : dp[row - 1][col + 1];
            int right_down = (row == n - 1 || col == m - 1) ? 0 : dp[row + 1][col + 1];

            dp[row][col] = mine[row][col] + max(right, max(right_up, right_down));
        }
    }

    int result = dp[0][0];
    for (int i = 1; i < n; i++) {
        if (dp[i][0] > result) {
            result = dp[i][0];
        }
    }

    for (int i = 0; i < n; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}

int main(void) {
    int n = 4;
    int m = 4;

    int **mine = (int **)malloc(n * sizeof(int *));
    if (mine == NULL) {
        return 1;
    }

    for (int i = 0; i < n; i++) {
        mine[i] = (int *)malloc(m * sizeof(int));
        if (mine[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(mine[j]);
            }
            free(mine);
            return 1;
        }
    }

    int data[4][4] = {
        {1, 3, 1, 5},
        {2, 2, 4, 1},
        {5, 0, 2, 3},
        {0, 6, 1, 2}
    };

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            mine[i][j] = data[i][j];
        }
    }

    int result = maxGold(n, m, mine);
    printf("%d\n", result);

    for (int i = 0; i < n; i++) {
        free(mine[i]);
    }
    free(mine);

    return 0;
}