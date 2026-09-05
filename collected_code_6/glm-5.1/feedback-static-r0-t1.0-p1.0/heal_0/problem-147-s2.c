#include <stdio.h>
#include <stdlib.h>

int maximumTotalPathSum(int **triangle, int numRows) {
    if (numRows <= 0) {
        return 0;
    }
    int *dp = (int *)malloc(numRows * sizeof(int));
    if (dp == NULL) {
        return 0;
    }
    for (int i = 0; i < numRows; i++) {
        dp[i] = triangle[numRows - 1][i];
    }
    for (int row = numRows - 2; row >= 0; row--) {
        for (int col = 0; col <= row; col++) {
            int left = dp[col];
            int right = dp[col + 1];
            int max = left > right ? left : right;
            dp[col] = triangle[row][col] + max;
        }
    }
    int result = dp[0];
    free(dp);
    return result;
}

int main(void) {
    int r0[] = {3};
    int r1[] = {7, 4};
    int r2[] = {2, 4, 6};
    int r3[] = {8, 5, 9, 3};
    int *triangle[] = {r0, r1, r2, r3};
    int numRows = 4;
    int sum = maximumTotalPathSum(triangle, numRows);
    printf("%d\n", sum);
    return 0;
}