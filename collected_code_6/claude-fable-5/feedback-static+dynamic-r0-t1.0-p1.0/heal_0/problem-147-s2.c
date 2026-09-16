#include <stdio.h>
#include <stdlib.h>

int max_path_sum(int **triangle, int rows)
{
    int *dp;
    int i;
    int j;
    int result;

    if (triangle == NULL || rows <= 0) {
        return 0;
    }

    dp = malloc((size_t)rows * sizeof(int));
    if (dp == NULL) {
        return 0;
    }

    for (j = 0; j < rows; j++) {
        dp[j] = triangle[rows - 1][j];
    }

    for (i = rows - 2; i >= 0; i--) {
        for (j = 0; j <= i; j++) {
            if (dp[j] > dp[j + 1]) {
                dp[j] = triangle[i][j] + dp[j];
            } else {
                dp[j] = triangle[i][j] + dp[j + 1];
            }
        }
    }

    result = dp[0];
    free(dp);
    return result;
}

int main(void)
{
    int rows = 4;
    int values[4][4] = {
        {1, 0, 0, 0},
        {2, 1, 0, 0},
        {3, 3, 2, 0},
        {4, 3, 1, 3}
    };
    int **triangle;
    int i;
    int j;
    int result;

    triangle = malloc((size_t)rows * sizeof(int *));
    if (triangle == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < rows; i++) {
        triangle[i] = malloc((size_t)rows * sizeof(int));
        if (triangle[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            for (j = 0; j < i; j++) {
                free(triangle[j]);
            }
            free(triangle);
            return EXIT_FAILURE;
        }
        for (j = 0; j < rows; j++) {
            triangle[i][j] = values[i][j];
        }
    }

    result = max_path_sum(triangle, rows);
    printf("Maximum path sum: %d\n", result);

    for (i = 0; i < rows; i++) {
        free(triangle[i]);
    }
    free(triangle);

    return EXIT_SUCCESS;
}