#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_max_gold(int **mine, int rows, int cols) {
    if (mine == NULL || rows <= 0 || cols <= 0) {
        return 0;
    }

    int **dp = (int **)malloc(rows * sizeof(int *));
    if (dp == NULL) {
        return 0;
    }

    for (int i = 0; i < rows; i++) {
        dp[i] = (int *)malloc(cols * sizeof(int));
        if (dp[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(dp[j]);
            }
            free(dp);
            return 0;
        }
    }

    for (int i = 0; i < rows; i++) {
        dp[i][cols - 1] = mine[i][cols - 1];
    }

    for (int j = cols - 2; j >= 0; j--) {
        for (int i = 0; i < rows; i++) {
            int right = dp[i][j + 1];
            int right_up = (i > 0) ? dp[i - 1][j + 1] : 0;
            int right_down = (i < rows - 1) ? dp[i + 1][j + 1] : 0;

            int max_right = right;
            if (right_up > max_right) {
                max_right = right_up;
            }
            if (right_down > max_right) {
                max_right = right_down;
            }

            dp[i][j] = mine[i][j] + max_right;
        }
    }

    int max_gold = dp[0][0];
    for (int i = 1; i < rows; i++) {
        if (dp[i][0] > max_gold) {
            max_gold = dp[i][0];
        }
    }

    for (int i = 0; i < rows; i++) {
        free(dp[i]);
    }
    free(dp);

    return max_gold;
}

int main(void) {
    int rows = 4;
    int cols = 4;

    int **mine = (int **)malloc(rows * sizeof(int *));
    if (mine == NULL) {
        return 1;
    }

    for (int i = 0; i < rows; i++) {
        mine[i] = (int *)malloc(cols * sizeof(int));
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

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            mine[i][j] = data[i][j];
        }
    }

    int result = get_max_gold(mine, rows, cols);
    printf("%d\n", result);

    for (int i = 0; i < rows; i++) {
        free(mine[i]);
    }
    free(mine);

    return 0;
}