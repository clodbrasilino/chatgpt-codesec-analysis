#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROWS 100

int max_path_sum(const int triangle[][MAX_ROWS], int rows, int *result)
{
    int dp[MAX_ROWS];
    int i;
    int j;

    if (triangle == NULL || result == NULL || rows <= 0 || rows > MAX_ROWS) {
        return -1;
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

    *result = dp[0];
    return 0;
}

int main(void)
{
    int triangle[MAX_ROWS][MAX_ROWS];
    int rows = 4;
    int result = 0;
    int values[4][4] = {
        {1, 0, 0, 0},
        {2, 1, 0, 0},
        {3, 3, 2, 0},
        {4, 1, 2, 6}
    };
    int i;
    int j;

    memset(triangle, 0, sizeof(triangle));

    for (i = 0; i < rows; i++) {
        for (j = 0; j <= i; j++) {
            triangle[i][j] = values[i][j];
        }
    }

    if (max_path_sum(triangle, rows, &result) != 0) {
        fprintf(stderr, "Error: invalid input to max_path_sum\n");
        return EXIT_FAILURE;
    }

    if (printf("Maximum total path sum: %d\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}