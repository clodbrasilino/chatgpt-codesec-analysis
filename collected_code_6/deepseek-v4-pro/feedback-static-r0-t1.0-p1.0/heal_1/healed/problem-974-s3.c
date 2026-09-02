#include <stdio.h>
#include <stdlib.h>

int minimumTotal(int** triangle, int triangleSize, const int* triangleColSize) {
    if (triangle == NULL || triangleSize <= 0 || triangleColSize == NULL) {
        return 0;
    }
    
    int* dp = (int*)malloc(triangleSize * sizeof(int));
    if (dp == NULL) {
        return 0;
    }
    
    for (int j = 0; j < triangleColSize[triangleSize - 1]; j++) {
        dp[j] = triangle[triangleSize - 1][j];
    }
    
    for (int i = triangleSize - 2; i >= 0; i--) {
        for (int j = 0; j < triangleColSize[i]; j++) {
            dp[j] = triangle[i][j] + (dp[j] < dp[j + 1] ? dp[j] : dp[j + 1]);
        }
    }
    
    int result = dp[0];
    free(dp);
    return result;
}

int main() {
    int rows = 4;
    int** triangle = (int**)malloc(rows * sizeof(int*));
    int* colSizes = (int*)malloc(rows * sizeof(int));
    
    int row0[] = {2};
    int row1[] = {3, 4};
    int row2[] = {6, 5, 7};
    int row3[] = {4, 1, 8, 3};
    
    triangle[0] = row0;
    triangle[1] = row1;
    triangle[2] = row2;
    triangle[3] = row3;
    
    colSizes[0] = 1;
    colSizes[1] = 2;
    colSizes[2] = 3;
    colSizes[3] = 4;
    
    int result = minimumTotal(triangle, rows, colSizes);
    printf("%d\n", result);
    
    free(triangle);
    free(colSizes);
    
    return 0;
}