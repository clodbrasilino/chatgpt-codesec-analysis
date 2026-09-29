#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int maxPathSum(int **triangle, int numRows) {
    if (triangle == NULL || numRows <= 0) {
        return 0;
    }
    
    int *dp = (int *)malloc((size_t)numRows * sizeof(int));
    if (dp == NULL) {
        return 0;
    }
    
    for (int i = 0; i < numRows; i++) {
        if (triangle[i] == NULL) {
            free(dp);
            return 0;
        }
        dp[i] = triangle[numRows - 1][i];
    }
    
    for (int row = numRows - 2; row >= 0; row--) {
        for (int col = 0; col <= row; col++) {
            int maxChild = (dp[col] > dp[col + 1]) ? dp[col] : dp[col + 1];
            if (triangle[row][col] > INT_MAX - maxChild) {
                free(dp);
                return 0;
            }
            dp[col] = triangle[row][col] + maxChild;
        }
    }
    
    int result = dp[0];
    free(dp);
    return result;
}

int main(void) {
    int numRows = 4;
    
    int **triangle = (int **)malloc((size_t)numRows * sizeof(int *));
    if (triangle == NULL) {
        return 1;
    }
    
    for (int i = 0; i < numRows; i++) {
        triangle[i] = (int *)malloc((size_t)(i + 1) * sizeof(int));
        if (triangle[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(triangle[j]);
            }
            free(triangle);
            return 1;
        }
    }
    
    triangle[0][0] = 3;
    triangle[1][0] = 7;
    triangle[1][1] = 4;
    triangle[2][0] = 2;
    triangle[2][1] = 4;
    triangle[2][2] = 6;
    triangle[3][0] = 8;
    triangle[3][1] = 5;
    triangle[3][2] = 9;
    triangle[3][3] = 3;
    
    int result = maxPathSum(triangle, numRows);
    printf("Maximum path sum: %d\n", result);
    
    for (int i = 0; i < numRows; i++) {
        free(triangle[i]);
    }
    free(triangle);
    
    return 0;
}