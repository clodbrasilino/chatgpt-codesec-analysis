#include <stdio.h>
#include <stdlib.h>

#define MAX_ROWS 100

int max_path_sum(int triangle[][MAX_ROWS], int num_rows) {
    if (num_rows <= 0 || num_rows > MAX_ROWS) {
        return 0;
    }

    int *dp = (int *)malloc(num_rows * sizeof(int));
    if (dp == NULL) {
        return 0;
    }

    for (int i = 0; i < num_rows; i++) {
        dp[i] = triangle[num_rows - 1][i];
    }

    for (int i = num_rows - 2; i >= 0; i--) {
        for (int j = 0; j <= i; j++) {
            if (dp[j] > dp[j + 1]) {
                dp[j] = dp[j] + triangle[i][j];
            } else {
                dp[j] = dp[j + 1] + triangle[i][j];
            }
        }
    }

    int max_sum = dp[0];
    free(dp);

    return max_sum;
}

int main() {
    int triangle[MAX_ROWS][MAX_ROWS] = {
        {3, 0, 0, 0},
        {7, 4, 0, 0},
        {2, 4, 6, 0},
        {8, 5, 9, 3}
    };
    int num_rows = 4;

    int result = max_path_sum(triangle, num_rows);
    printf("Maximum total path sum: %d\n", result);

    return 0;
}