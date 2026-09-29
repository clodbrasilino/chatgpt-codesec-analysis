#include <stdio.h>
#include <stdlib.h>

int minimumTotal(int** triangle, int triangleSize, const int* triangleColSizes) {
    if (triangleSize == 0 || triangle == NULL) {
        return 0;
    }

    int* dp = (int*)malloc(triangleSize * sizeof(int));
    if (dp == NULL) {
        return 0;
    }

    for (int i = 0; i < triangleColSizes[triangleSize - 1]; i++) {
        dp[i] = triangle[triangleSize - 1][i];
    }

    for (int i = triangleSize - 2; i >= 0; i--) {
        for (int j = 0; j < triangleColSizes[i]; j++) {
            if (dp[j] < dp[j + 1]) {
                dp[j] = triangle[i][j] + dp[j];
            } else {
                dp[j] = triangle[i][j] + dp[j + 1];
            }
        }
    }

    int result = dp[0];
    free(dp);
    return result;
}

int main() {
    int triangleSize = 4;
    int* triangleColSizes = (int*)malloc(triangleSize * sizeof(int));
    int** triangle = (int**)malloc(triangleSize * sizeof(int*));

    triangleColSizes[0] = 1;
    triangle[0] = (int*)malloc(triangleColSizes[0] * sizeof(int));
    triangle[0][0] = 2;

    triangleColSizes[1] = 2;
    triangle[1] = (int*)malloc(triangleColSizes[1] * sizeof(int));
    triangle[1][0] = 3;
    triangle[1][1] = 4;

    triangleColSizes[2] = 3;
    triangle[2] = (int*)malloc(triangleColSizes[2] * sizeof(int));
    triangle[2][0] = 6;
    triangle[2][1] = 5;
    triangle[2][2] = 7;

    triangleColSizes[3] = 4;
    triangle[3] = (int*)malloc(triangleColSizes[3] * sizeof(int));
    triangle[3][0] = 4;
    triangle[3][1] = 1;
    triangle[3][2] = 8;
    triangle[3][3] = 3;

    int result = minimumTotal(triangle, triangleSize, triangleColSizes);
    printf("%d\n", result);

    for (int i = 0; i < triangleSize; i++) {
        free(triangle[i]);
    }
    free(triangle);
    free(triangleColSizes);

    return 0;
}