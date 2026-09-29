#include <stdio.h>
#include <stdlib.h>

int maximum_path_sum(int **triangle, int rows) {
    if (triangle == NULL || rows <= 0) {
        return 0;
    }
    if (triangle[0] == NULL) {
        return 0;
    }

    int *dp = (int *)malloc(rows * sizeof(int));
    if (dp == NULL) {
        return 0;
    }

    for (int i = 0; i < rows; i++) {
        dp[i] = triangle[rows - 1][i];
    }

    for (int i = rows - 2; i >= 0; i--) {
        if (triangle[i] == NULL) {
            free(dp);
            return 0;
        }
        for (int j = 0; j <= i; j++) {
            int left = dp[j];
            int right = dp[j + 1];
            dp[j] = triangle[i][j] + (left > right ? left : right);
        }
    }

    int result = dp[0];
    free(dp);
    return result;
}

int main(void) {
    int rows = 4;
    int **triangle = (int **)malloc(rows * sizeof(int *));
    if (triangle == NULL) {
        return EXIT_FAILURE;
    }

    for (int i = 0; i < rows; i++) {
        triangle[i] = (int *)malloc((i + 1) * sizeof(int));
        if (triangle[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(triangle[j]);
            }
            free(triangle);
            return EXIT_FAILURE;
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

    int result = maximum_path_sum(triangle, rows);
    printf("%d\n", result);

    for (int i = 0; i < rows; i++) {
        free(triangle[i]);
    }
    free(triangle);

    return EXIT_SUCCESS;
}