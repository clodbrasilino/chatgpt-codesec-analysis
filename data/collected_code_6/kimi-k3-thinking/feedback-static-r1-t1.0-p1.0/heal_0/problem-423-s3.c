#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int max_of_three(int a, int b, int c)
{
    int max_value = a;

    if (b > max_value) {
        max_value = b;
    }
    if (c > max_value) {
        max_value = c;
    }

    return max_value;
}

int gold_mine_max(const int *mine, size_t rows, size_t cols, int *result)
{
    int *dp;
    int max_gold;
    size_t r;
    size_t c;

    if (mine == NULL || result == NULL || rows == 0U || cols == 0U) {
        return -1;
    }

    if (rows > SIZE_MAX / cols || (rows * cols) > SIZE_MAX / sizeof(*dp)) {
        return -1;
    }

    dp = malloc(rows * cols * sizeof(*dp));
    if (dp == NULL) {
        return -1;
    }

    for (r = 0U; r < rows; r++) {
        dp[r * cols + (cols - 1U)] = mine[r * cols + (cols - 1U)];
    }

    c = cols - 1U;
    while (c > 0U) {
        c--;
        for (r = 0U; r < rows; r++) {
            int right = dp[r * cols + (c + 1U)];
            int right_up = (r > 0U) ? dp[(r - 1U) * cols + (c + 1U)] : 0;
            int right_down = (r < (rows - 1U)) ? dp[(r + 1U) * cols + (c + 1U)] : 0;

            dp[r * cols + c] = mine[r * cols + c] + max_of_three(right, right_up, right_down);
        }
    }

    max_gold = dp[0];
    for (r = 1U; r < rows; r++) {
        if (dp[r * cols] > max_gold) {
            max_gold = dp[r * cols];
        }
    }

    free(dp);
    dp = NULL;

    *result = max_gold;

    return 0;
}

int main(void)
{
    size_t rows;
    size_t cols;
    size_t total;
    size_t i;
    int *mine;
    int result;

    if (scanf("%zu %zu", &rows, &cols) != 2) {
        fprintf(stderr, "Error: failed to read dimensions\n");
        return EXIT_FAILURE;
    }

    if (rows == 0U || cols == 0U || rows > SIZE_MAX / cols) {
        fprintf(stderr, "Error: invalid dimensions\n");
        return EXIT_FAILURE;
    }

    total = rows * cols;

    if (total > SIZE_MAX / sizeof(*mine)) {
        fprintf(stderr, "Error: dimensions too large\n");
        return EXIT_FAILURE;
    }

    mine = malloc(total * sizeof(*mine));
    if (mine == NULL) {
        fprintf(stderr, "Error: memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (i = 0U; i < total; i++) {
        if (scanf("%d", &mine[i]) != 1) {
            fprintf(stderr, "Error: failed to read mine data\n");
            free(mine);
            mine = NULL;
            return EXIT_FAILURE;
        }
        if (mine[i] < 0) {
            fprintf(stderr, "Error: gold amounts must be non-negative\n");
            free(mine);
            mine = NULL;
            return EXIT_FAILURE;
        }
    }

    if (gold_mine_max(mine, rows, cols, &result) != 0) {
        fprintf(stderr, "Error: computation failed\n");
        free(mine);
        mine = NULL;
        return EXIT_FAILURE;
    }

    free(mine);
    mine = NULL;

    printf("%d\n", result);

    return EXIT_SUCCESS;
}