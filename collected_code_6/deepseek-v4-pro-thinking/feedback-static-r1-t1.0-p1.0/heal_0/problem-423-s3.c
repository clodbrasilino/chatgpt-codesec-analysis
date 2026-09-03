#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int max_gold(int rows, int cols, int **gold) {
    int i;
    int j;
    int best;
    int right;
    int right_up;
    int right_down;
    int max;
    int **dp;

    if (rows <= 0 || cols <= 0 || gold == NULL) {
        return -1;
    }

    for (i = 0; i < rows; ++i) {
        if (gold[i] == NULL) {
            return -1;
        }
    }

    dp = calloc((size_t)rows, sizeof(*dp));
    if (dp == NULL) {
        return -1;
    }

    for (i = 0; i < rows; ++i) {
        dp[i] = calloc((size_t)cols, sizeof(*dp[i]));
        if (dp[i] == NULL) {
            for (j = 0; j < i; ++j) {
                free(dp[j]);
            }
            free(dp);
            return -1;
        }
    }

    for (i = 0; i < rows; ++i) {
        dp[i][cols - 1] = gold[i][cols - 1];
    }

    for (j = cols - 2; j >= 0; --j) {
        for (i = 0; i < rows; ++i) {
            right = dp[i][j + 1];
            right_up = (i > 0) ? dp[i - 1][j + 1] : INT_MIN;
            right_down = (i < rows - 1) ? dp[i + 1][j + 1] : INT_MIN;

            best = right;
            if (right_up > best) {
                best = right_up;
            }
            if (right_down > best) {
                best = right_down;
            }

            dp[i][j] = gold[i][j] + best;
        }
    }

    max = dp[0][0];
    for (i = 1; i < rows; ++i) {
        if (dp[i][0] > max) {
            max = dp[i][0];
        }
    }

    for (i = 0; i < rows; ++i) {
        free(dp[i]);
    }
    free(dp);

    return max;
}

int main(void) {
    int rows = 4;
    int cols = 4;
    int data[4][4] = {
        {1, 3, 1, 5},
        {2, 2, 4, 1},
        {5, 0, 2, 3},
        {0, 6, 1, 2}
    };
    int *gold[4];
    int i;
    int result;

    for (i = 0; i < rows; ++i) {
        gold[i] = data[i];
    }

    result = max_gold(rows, cols, gold);
    if (result < 0) {
        fprintf(stderr, "Error computing maximum gold\n");
        return 1;
    }

    printf("%d\n", result);
    return 0;
}