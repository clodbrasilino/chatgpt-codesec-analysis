#include <stdio.h>
#include <stdlib.h>

#define MAX_ROWS 100

int maxPathSum(int triangle[][MAX_ROWS], int numRows) {
    if (numRows <= 0) {
        return 0;
    }

    int *dp = (int *)malloc(numRows * sizeof(int));
    if (dp == NULL) {
        return -1;
    }

    for (int i = 0; i < numRows; i++) {
        dp[i] = triangle[numRows - 1][i];
    }

    for (int i = numRows - 2; i >= 0; i--) {
        for (int j = 0; j <= i; j++) {
            int max_val = dp[j] > dp[j + 1] ? dp[j] : dp[j + 1];
            dp[j] = triangle[i][j] + max_val;
        }
    }

    int result = dp[0];
    free(dp);

    return result;
}

int main() {
    int triangle[MAX_ROWS][MAX_ROWS] = {
        {3, 0, 0, 0},
        {7, 4, 0, 0},
        {2, 4, 6, 0},
        {8, 5, 9, 3}
    };
    int numRows = 4;

    int max_sum = maxPathSum(triangle, numRows);

    if (max_sum == -1) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("%d\n", max_sum);

    return EXIT_SUCCESS;
}