#include <stdio.h>
#include <stdlib.h>

int get_max_gold(int **mine, int m, int n);

int get_max_gold(int **mine, int m, int n) {
    if (!mine || m <= 0 || n <= 0) {
        return 0;
    }

    int **dp = (int **)malloc((size_t)m * sizeof(int *));
    if (!dp) {
        return -1;
    }

    for (int i = 0; i < m; i++) {
        dp[i] = (int *)malloc((size_t)n * sizeof(int));
        if (!dp[i]) {
            for (int j = 0; j < i; j++) {
                free(dp[j]);
            }
            free(dp);
            return -1;
        }
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            dp[i][j] = mine[i][j];
        }
    }

    for (int col = n - 2; col >= 0; col--) {
        for (int row = 0; row < m; row++) {
            int right = dp[row][col + 1];
            int right_up = (row == 0) ? 0 : dp[row - 1][col + 1];
            int right_down = (row == m - 1) ? 0 : dp[row + 1][col + 1];

            int max_step = right;
            if (right_up > max_step) {
                max_step = right_up;
            }
            if (right_down > max_step) {
                max_step = right_down;
            }

            dp[row][col] = mine[row][col] + max_step;
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

int main(void) {
    int m = 4;
    int n = 4;

    int **mine = (int **)malloc((size_t)m * sizeof(int *));
    if (!mine) {
        return EXIT_FAILURE;
    }

    for (int i = 0; i < m; i++) {
        mine[i] = (int *)malloc((size_t)n * sizeof(int));
        if (!mine[i]) {
            for (int j = 0; j < i; j++) {
                free(mine[j]);
            }
            free(mine);
            return EXIT_FAILURE;
        }
    }

    int initial_mine[4][4] = {
        {1, 3, 1, 5},
        {2, 2, 4, 1},
        {5, 0, 2, 3},
        {0, 6, 1, 2}
    };

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            mine[i][j] = initial_mine[i][j];
        }
    }

    int result = get_max_gold(mine, m, n);
    if (result == -1) {
        for (int i = 0; i < m; i++) {
            free(mine[i]);
        }
        free(mine);
        return EXIT_FAILURE;
    }

    printf("%d\n", result);

    for (int i = 0; i < m; i++) {
        free(mine[i]);
    }
    free(mine);

    return EXIT_SUCCESS;
}