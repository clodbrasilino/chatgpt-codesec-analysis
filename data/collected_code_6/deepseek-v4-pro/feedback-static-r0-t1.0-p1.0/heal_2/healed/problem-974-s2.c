#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int minimumTotal(int** triangle, int triangleSize, const int* triangleColSize) {
    if (triangle == NULL || triangleSize <= 0 || triangleColSize == NULL) {
        return 0;
    }

    int* dp = (int*)malloc(triangleSize * sizeof(int));
    if (dp == NULL) {
        return 0;
    }

    dp[0] = triangle[0][0];

    for (int i = 1; i < triangleSize; i++) {
        if (triangle[i] == NULL || triangleColSize[i] <= 0) {
            free(dp);
            return 0;
        }
        
        dp[i] = dp[i - 1] + triangle[i][i];
        for (int j = i - 1; j > 0; j--) {
            dp[j] = (dp[j] < dp[j - 1] ? dp[j] : dp[j - 1]) + triangle[i][j];
        }
        dp[0] = dp[0] + triangle[i][0];
    }

    int minSum = INT_MAX;
    for (int i = 0; i < triangleSize; i++) {
        if (dp[i] < minSum) {
            minSum = dp[i];
        }
    }

    free(dp);
    return minSum;
}

int main(void) {
    int row1[] = {2};
    int row2[] = {3, 4};
    int row3[] = {6, 5, 7};
    int row4[] = {4, 1, 8, 3};

    int* triangle[] = {row1, row2, row3, row4};
    const int colSize[] = {1, 2, 3, 4};

    int result = minimumTotal(triangle, 4, colSize);
    printf("%d\n", result);

    return 0;
}