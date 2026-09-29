#include <stdio.h>
#include <stdlib.h>

int minimumTotal(int** triangle, int triangleSize, const int* triangleColSize) {
    if (triangleSize == 0 || triangle == NULL || triangleColSize == NULL) {
        return 0;
    }

    int* dp = (int*)malloc(triangleSize * sizeof(int));
    if (dp == NULL) {
        return 0;
    }

    for (int i = 0; i < triangleSize; i++) {
        dp[i] = triangle[triangleSize - 1][i];
    }

    for (int i = triangleSize - 2; i >= 0; i--) {
        for (int j = 0; j <= i; j++) {
            dp[j] = triangle[i][j] + (dp[j] < dp[j + 1] ? dp[j] : dp[j + 1]);
        }
    }

    int minSum = dp[0];
    free(dp);

    return minSum;
}

int main() {
    int triangleSize = 4;
    /* Possible weaknesses found:
     *  Variable 'colSizes' can be declared as const array [constVariable]
     */
    int colSizes[] = {1, 2, 3, 4};
    
    int** triangle = (int**)malloc(triangleSize * sizeof(int*));
    if (triangle == NULL) {
        return 1;
    }

    for (int i = 0; i < triangleSize; i++) {
        triangle[i] = (int*)malloc(colSizes[i] * sizeof(int));
        if (triangle[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(triangle[j]);
            }
            free(triangle);
            return 1;
        }
    }

    triangle[0][0] = 2;
    triangle[1][0] = 3; 
    triangle[1][1] = 4;
    triangle[2][0] = 6; 
    triangle[2][1] = 5; 
    triangle[2][2] = 7;
    triangle[3][0] = 4; 
    triangle[3][1] = 1; 
    triangle[3][2] = 8; 
    triangle[3][3] = 3;

    int minPathSum = minimumTotal(triangle, triangleSize, colSizes);
    printf("%d\n", minPathSum);

    for (int i = 0; i < triangleSize; i++) {
        free(triangle[i]);
    }
    free(triangle);

    return 0;
}