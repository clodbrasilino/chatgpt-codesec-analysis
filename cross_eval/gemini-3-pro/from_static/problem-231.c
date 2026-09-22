#include <stdio.h>
#include <stdlib.h>

#define ROWS 4

int findMaxSum(int triangle[ROWS][ROWS], int rows) {
    if (rows <= 0) {
        return 0;
    }

    int *dp = (int *)malloc(rows * sizeof(int));
    if (dp == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < rows; ++i) {
        dp[i] = triangle[rows - 1][i];
    }

    for (int i = rows - 2; i >= 0; --i) {
        for (int j = 0; j <= i; ++j) {
            int max_val = (dp[j] > dp[j + 1]) ? dp[j] : dp[j + 1];
            dp[j] = triangle[i][j] + max_val;
        }
    }

    int result = dp[0];
    free(dp);

    return result;
}

int main(void) {
    int triangle[ROWS][ROWS] = {
        {3, 0, 0, 0},
        {7, 4, 0, 0},
        {2, 4, 6, 0},
        {8, 5, 9, 3}
    };

    int max_sum = findMaxSum(triangle, ROWS);
    printf("%d\n", max_sum);

    return EXIT_SUCCESS;
}