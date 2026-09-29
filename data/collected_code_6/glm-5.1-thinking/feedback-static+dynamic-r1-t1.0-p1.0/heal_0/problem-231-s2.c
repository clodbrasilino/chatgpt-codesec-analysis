#include <stdio.h>
#include <stdlib.h>

int max_triangle_sum(const int *triangle, int rows) {
    int *dp;
    int i;
    int j;
    int max_val;
    int result;

    if (triangle == NULL || rows <= 0) {
        return 0;
    }

    dp = (int *)malloc(rows * sizeof(int));
    if (dp == NULL) {
        return 0;
    }

    for (i = 0; i < rows; i++) {
        dp[i] = triangle[(rows - 1) * rows / 2 + i];
    }

    for (i = rows - 2; i >= 0; i--) {
        for (j = 0; j <= i; j++) {
            max_val = (dp[j] > dp[j + 1]) ? dp[j] : dp[j + 1];
            dp[j] = triangle[i * (i + 1) / 2 + j] + max_val;
        }
    }

    result = dp[0];
    free(dp);

    return result;
}

int main(void) {
    int triangle[] = {
        3,
        7, 4,
        2, 4, 6,
        8, 5, 9, 3
    };
    int rows = 4;
    int max_sum;

    max_sum = max_triangle_sum(triangle, rows);
    printf("%d\n", max_sum);

    return 0;
}