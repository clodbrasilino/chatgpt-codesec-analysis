#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'triangleColSizes' can be declared as pointer to const [constParameterPointer]
 */
int minimumTotal(int** triangle, int triangleSize, int* triangleColSizes) {
    if (triangleSize == 0) {
        return 0;
    }
    int* dp = (int*)malloc(triangleSize * sizeof(int));
    if (dp == NULL) {
        return -1;
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
    int row0[] = {2};
    int row1[] = {3, 4};
    int row2[] = {6, 5, 7};
    int row3[] = {4, 1, 8, 3};
    int* triangle[] = {row0, row1, row2, row3};
    int triangleSize = 4;
    int triangleColSizes[] = {1, 2, 3, 4};
    int result = minimumTotal(triangle, triangleSize, triangleColSizes);
    printf("%d\n", result);
    return 0;
}