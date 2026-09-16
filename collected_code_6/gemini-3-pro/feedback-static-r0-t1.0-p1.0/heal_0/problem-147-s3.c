#include <stdio.h>
#include <stdlib.h>

int maxPathSum(int** triangle, int numRows) {
    if (triangle == NULL || numRows <= 0) {
        return 0;
    }

    int* dp = (int*)malloc(numRows * sizeof(int));
    if (dp == NULL) {
        return 0;
    }

    for (int i = 0; i < numRows; i++) {
        dp[i] = triangle[numRows - 1][i];
    }

    for (int i = numRows - 2; i >= 0; i--) {
        for (int j = 0; j <= i; j++) {
            int left = dp[j];
            int right = dp[j + 1];
            dp[j] = triangle[i][j] + (left > right ? left : right);
        }
    }

    int maxSum = dp[0];
    free(dp);
    return maxSum;
}

int main() {
    int numRows = 4;
    
    int** triangle = (int**)malloc(numRows * sizeof(int*));
    if (triangle == NULL) {
        return 1;
    }

    for (int i = 0; i < numRows; i++) {
        triangle[i] = (int*)malloc((i + 1) * sizeof(int));
        if (triangle[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(triangle[j]);
            }
            free(triangle);
            return 1;
        }
    }

    triangle[0][0] = 3;
    triangle[1][0] = 7; triangle[1][1] = 4;
    triangle[2][0] = 2; triangle[2][1] = 4; triangle[2][2] = 6;
    triangle[3][0] = 8; triangle[3][1] = 5; triangle[3][2] = 9; triangle[3][3] = 3;

    int result = maxPathSum(triangle, numRows);
    printf("Max path sum: %d\n", result);

    for (int i = 0; i < numRows; i++) {
        free(triangle[i]);
    }
    free(triangle);

    return 0;
}