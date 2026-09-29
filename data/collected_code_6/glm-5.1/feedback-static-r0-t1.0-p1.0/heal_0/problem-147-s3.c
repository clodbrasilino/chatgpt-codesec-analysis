#include <stdio.h>
#include <stdlib.h>

int maximum_path_sum(int **triangle, int rows) {
    if (triangle == NULL || rows <= 0) {
        return 0;
    }
    int *dp = (int *)malloc(rows * sizeof(int));
    if (dp == NULL) {
        return 0;
    }
    for (int i = 0; i < rows; i++) {
        dp[i] = triangle[rows - 1][i];
    }
    for (int i = rows - 2; i >= 0; i--) {
        for (int j = 0; j <= i; j++) {
            int left = dp[j];
            int right = dp[j + 1];
            dp[j] = triangle[i][j] + (left > right ? left : right);
        }
    }
    int result = dp[0];
    free(dp);
    return result;
}

int main(void) {
    int r1[] = {2};
    int r2[] = {3, 4};
    int r3[] = {6, 5, 7};
    int r4[] = {4, 1, 8, 3};
    int *triangle[] = {r1, r2, r3, r4};
    int rows = 4;
    int result = maximum_path_sum(triangle, rows);
    printf("%d\n", result);
    return 0;
}