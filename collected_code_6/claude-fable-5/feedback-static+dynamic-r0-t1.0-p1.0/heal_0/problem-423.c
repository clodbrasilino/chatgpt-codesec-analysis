#include <stdio.h>
#include <stdlib.h>

int max_of_three(int a, int b, int c)
{
    int m = a;
    if (b > m) {
        m = b;
    }
    if (c > m) {
        m = c;
    }
    return m;
}

int gold_mine_max(const int *mine, size_t rows, size_t cols)
{
    int **dp;
    size_t i;
    size_t j;
    size_t col;
    int result;
    int right;
    int right_up;
    int right_down;

    if (mine == NULL || rows == 0 || cols == 0) {
        return 0;
    }

    dp = malloc(rows * sizeof(int *));
    if (dp == NULL) {
        return -1;
    }

    for (i = 0; i < rows; i++) {
        dp[i] = calloc(cols, sizeof(int));
        if (dp[i] == NULL) {
            for (j = 0; j < i; j++) {
                free(dp[j]);
            }
            free(dp);
            return -1;
        }
    }

    for (col = cols; col > 0; col--) {
        j = col - 1;
        for (i = 0; i < rows; i++) {
            if (j == cols - 1) {
                right = 0;
            } else {
                right = dp[i][j + 1];
            }

            if (j == cols - 1 || i == 0) {
                right_up = 0;
            } else {
                right_up = dp[i - 1][j + 1];
            }

            if (j == cols - 1 || i == rows - 1) {
                right_down = 0;
            } else {
                right_down = dp[i + 1][j + 1];
            }

            dp[i][j] = mine[i * cols + j] + max_of_three(right, right_up, right_down);
        }
    }

    result = dp[0][0];
    for (i = 1; i < rows; i++) {
        if (dp[i][0] > result) {
            result = dp[i][0];
        }
    }

    for (i = 0; i < rows; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}

int main(void)
{
    int mine[4][4] = {
        {1, 3, 1, 5},
        {2, 2, 4, 1},
        {5, 0, 2, 3},
        {0, 6, 1, 2}
    };
    int answer;

    answer = gold_mine_max(&mine[0][0], 4, 4);
    if (answer < 0) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (printf("Maximum gold collected: %d\n", answer) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}