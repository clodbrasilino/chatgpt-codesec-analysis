#include <stdio.h>
#include <stdlib.h>

int find_max_sum(int **triangle, int n) {
    if (triangle == NULL || n <= 0) {
        return 0;
    }
    int **dp = (int **)malloc(n * sizeof(int *));
    if (dp == NULL) {
        return 0;
    }
    for (int i = 0; i < n; i++) {
        dp[i] = (int *)malloc((i + 1) * sizeof(int));
        if (dp[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(dp[j]);
            }
            free(dp);
            return 0;
        }
    }
    dp[0][0] = triangle[0][0];
    for (int i = 1; i < n; i++) {
        dp[i][0] = dp[i - 1][0] + triangle[i][0];
        dp[i][i] = dp[i - 1][i - 1] + triangle[i][i];
        for (int j = 1; j < i; j++) {
            int left = dp[i - 1][j - 1];
            int right = dp[i - 1][j];
            dp[i][j] = (left > right ? left : right) + triangle[i][j];
        }
    }
    int max_sum = dp[n - 1][0];
    for (int i = 1; i < n; i++) {
        if (dp[n - 1][i] > max_sum) {
            max_sum = dp[n - 1][i];
        }
    }
    for (int i = 0; i < n; i++) {
        free(dp[i]);
    }
    free(dp);
    return max_sum;
}

int main(void) {
    int n = 4;
    int *triangle_data[4];
    int r0[] = {1};
    int r1[] = {2, 3};
    int r2[] = {6, 5, 4};
    int r3[] = {10, 7, 8, 9};
    triangle_data[0] = r0;
    triangle_data[1] = r1;
    triangle_data[2] = r2;
    triangle_data[3] = r3;
    int result = find_max_sum(triangle_data, n);
    printf("%d\n", result);
    return 0;
}