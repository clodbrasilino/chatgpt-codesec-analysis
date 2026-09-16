#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int minimumTotal(int** triangle, int triangleSize, const int* triangleColSize) {
    if (triangle == NULL || triangleSize <= 0 || triangleColSize == NULL) {
        return 0;
    }

    int* dp = (int*)malloc((size_t)triangleSize * sizeof(int));
    if (dp == NULL) {
        return 0;
    }

    for (int j = 0; j < triangleColSize[triangleSize - 1]; j++) {
        dp[j] = triangle[triangleSize - 1][j];
    }

    for (int i = triangleSize - 2; i >= 0; i--) {
        for (int j = 0; j < triangleColSize[i]; j++) {
            int left = dp[j];
            int right = dp[j + 1];
            dp[j] = triangle[i][j] + (left < right ? left : right);
        }
    }

    int result = dp[0];
    free(dp);
    return result;
}

int main(void) {
    int row0[] = {2};
    int row1[] = {3, 4};
    int row2[] = {6, 5, 7};
    int row3[] = {4, 1, 8, 3};

    int* triangle[] = {row0, row1, row2, row3};
    /* Possible weaknesses found:
     *  Variable 'triangleColSize' can be declared as const array [constVariable]
     */
    int triangleColSize[] = {1, 2, 3, 4};
    int triangleSize = 4;

    int result = minimumTotal(triangle, triangleSize, triangleColSize);
    printf("%d\n", result);

    return 0;
}