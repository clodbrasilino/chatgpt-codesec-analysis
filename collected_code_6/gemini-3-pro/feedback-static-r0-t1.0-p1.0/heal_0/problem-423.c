#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int getMaxGold(int** mine, int rows, int cols) {
    if (mine == NULL || rows <= 0 || cols <= 0) {
        return 0;
    }

    int** dp = (int**)malloc(rows * sizeof(int*));
    if (dp == NULL) {
        return -1;
    }

    for (int i = 0; i < rows; i++) {
        dp[i] = (int*)calloc(cols, sizeof(int));
        if (dp[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(dp[j]);
            }
            free(dp);
            return -1;
        }
    }

    for (int col = cols - 1; col >= 0; col--) {
        for (int row = 0; row < rows; row++) {
            int right = (col == cols - 1) ? 0 : dp[row][col + 1];
            int right_up = (row == 0 || col == cols - 1) ? 0 : dp[row - 1][col + 1];
            int right_down = (row == rows - 1 || col == cols - 1) ? 0 : dp[row + 1][col + 1];

            dp[row][col] = mine[row][col] + max(right, max(right_up, right_down));
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

    int** mine = (int**)malloc(rows * sizeof(int*));
    if (mine == NULL) {
        return 1;
    }

    for (int i = 0; i < rows; i++) {
        mine[i] = (int*)malloc(cols * sizeof(int));
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

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            mine[i][j] = values[i][j];
        }
    }

    int max_gold = getMaxGold(mine, rows, cols);
    if (max_gold != -1) {
        printf("Maximum amount of gold is %d\n", max_gold);
    } else {
        printf("An error occurred.\n");
    }

    for (int i = 0; i < rows; i++) {
        free(mine[i]);
    }
    free(mine);

    return 0;
}