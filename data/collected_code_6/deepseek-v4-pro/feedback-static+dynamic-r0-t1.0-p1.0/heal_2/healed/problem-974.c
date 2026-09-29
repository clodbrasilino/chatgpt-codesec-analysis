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

    for (int i = 0; i < triangleSize; i++) {
        if (triangleColSize[i] <= i) {
            free(dp);
            return 0;
        }
    }

    dp[0] = triangle[0][0];

    for (int i = 1; i < triangleSize; i++) {
        for (int j = i; j >= 0; j--) {
            if (j == 0) {
                dp[j] = dp[j] + triangle[i][j];
            } else if (j == i) {
                dp[j] = dp[j - 1] + triangle[i][j];
            } else {
                dp[j] = (dp[j] < dp[j - 1] ? dp[j] : dp[j - 1]) + triangle[i][j];
            }
        }
    }

    int result = INT_MAX;
    for (int i = 0; i < triangleSize; i++) {
        if (dp[i] < result) {
            result = dp[i];
        }
    }

    free(dp);
    return result;
}

int main(void) {
    int row1[] = {2};
    int row2[] = {3, 4};
    int row3[] = {6, 5, 7};
    int row4[] = {4, 1, 8, 3};

    int* triangle[] = {row1, row2, row3, row4};
    const int triangleColSize[] = {1, 2, 3, 4};

    int result = minimumTotal(triangle, 4, triangleColSize);
    printf("%d\n", result);

    return 0;
}