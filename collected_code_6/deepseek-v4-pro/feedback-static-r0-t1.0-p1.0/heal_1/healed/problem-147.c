#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max_total_path_sum(int **triangle, const int *row_sizes, int rows) {
    if (rows <= 0 || triangle == NULL || row_sizes == NULL) {
        return 0;
    }
    
    for (int i = 0; i < rows; i++) {
        if (triangle[i] == NULL || row_sizes[i] != i + 1) {
            return 0;
        }
    }
    
    int *dp = (int *)malloc(rows * sizeof(int));
    if (dp == NULL) {
        return 0;
    }
    
    for (int i = 0; i < rows; i++) {
        dp[i] = triangle[rows - 1][i];
    }
    
    for (int i = rows - 2; i >= 0; i--) {
        for (int j = 0; j <= i; j++) {
            dp[j] = triangle[i][j] + (dp[j] > dp[j + 1] ? dp[j] : dp[j + 1]);
        }
    }
    
    int result = dp[0];
    free(dp);
    return result;
}

int main(void) {
    int rows1[] = {5};
    int rows2[] = {3, 7};
    int rows3[] = {8, 1, 6};
    int rows4[] = {2, 4, 9, 3};
    int rows5[] = {1, 5, 7, 2, 8};
    
    int *triangle[] = {rows1, rows2, rows3, rows4, rows5};
    int row_sizes[] = {1, 2, 3, 4, 5};
    
    int result = max_total_path_sum(triangle, row_sizes, 5);
    printf("Maximum path sum: %d\n", result);
    
    int tri1[] = {1};
    int tri2[] = {2, 3};
    int *triangle2[] = {tri1, tri2};
    int row_sizes2[] = {1, 2};
    
    int result2 = max_total_path_sum(triangle2, row_sizes2, 2);
    printf("Maximum path sum: %d\n", result2);
    
    int result3 = max_total_path_sum(NULL, NULL, 0);
    printf("Maximum path sum: %d\n", result3);
    
    return 0;
}