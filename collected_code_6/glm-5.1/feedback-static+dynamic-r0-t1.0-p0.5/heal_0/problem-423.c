#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int getMaxGold(int **mine, int m, int n) {
    int **dp = (int **)malloc(m * sizeof(int *));
    if (dp == NULL) {
        return -1;
    }
    for (int i = 0; i < m; i++) {
        dp[i] = (int *)malloc(n * sizeof(int));
        if (dp[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(dp[j]);
            }
            free(dp);
            return -1;
        }
    }

    for (int y = n - 1; y >= 0; y--) {
        for (int x = 0; x < m; x++) {
            int right = (y == n - 1) ? 0 : dp[x][y + 1];
            int right_up = (x == 0 || y == n - 1) ? 0 : dp[x - 1][y + 1];
            int right_down = (x == m - 1 || y == n - 1) ? 0 : dp[x + 1][y + 1];
            dp[x][y] = mine[x][y] + max(right, max(right_up, right_down));
        }
    }

    int result = dp[0][0];
    for (int i = 1; i < m; i++) {
        if (dp[i][0] > result) {
            result = dp[i][0];
        }
    }

    for (int i = 0; i < m; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}

int main() {
    int m = 4;
    int n = 4;

    int **mine = (int **)malloc(m * sizeof(int *));
    if (mine == NULL) {
        return EXIT_FAILURE;
    }
    for (int i = 0; i < m; i++) {
        mine[i] = (int *)malloc(n * sizeof(int));
        if (mine[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(mine[j]);
            }
            free(mine);
            return EXIT_FAILURE;
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

    int max_gold = getMaxGold(mine, m, n);
    if (max_gold == -1) {
        for (int i = 0; i < m; i++) {
            free(mine[i]);
        }
        free(mine);
        return EXIT_FAILURE;
    }

    printf("%d\n", max_gold);

    for (int i = 0; i < m; i++) {
        free(mine[i]);
    }
    free(mine);

    return EXIT_SUCCESS;
}