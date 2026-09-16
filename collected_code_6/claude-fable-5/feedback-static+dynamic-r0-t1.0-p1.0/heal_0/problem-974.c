#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static long min_long(long a, long b)
{
    return (a < b) ? a : b;
}

static int minimum_path_sum(const int *const *triangle, size_t rows, long *result)
{
    long *dp;
    size_t i;
    size_t j;

    if (triangle == NULL || result == NULL || rows == 0U) {
        return -1;
    }

    dp = malloc(rows * sizeof *dp);
    if (dp == NULL) {
        return -1;
    }

    for (j = 0U; j < rows; j++) {
        if (triangle[rows - 1U] == NULL) {
            free(dp);
            return -1;
        }
        dp[j] = (long)triangle[rows - 1U][j];
    }

    for (i = rows - 1U; i > 0U; i--) {
        size_t row = i - 1U;
        if (triangle[row] == NULL) {
            free(dp);
            return -1;
        }
        for (j = 0U; j <= row; j++) {
            dp[j] = (long)triangle[row][j] + min_long(dp[j], dp[j + 1U]);
        }
    }

    *result = dp[0];
    free(dp);
    return 0;
}

int main(void)
{
    static const int row0[] = { 2 };
    static const int row1[] = { 3, 4 };
    static const int row2[] = { 6, 5, 7 };
    static const int row3[] = { 4, 1, 8, 3 };
    const int *triangle[] = { row0, row1, row2, row3 };
    long result = 0;

    if (minimum_path_sum(triangle, 4U, &result) != 0) {
        if (fprintf(stderr, "Error computing minimum path sum\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("Minimum total path sum: %ld\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}