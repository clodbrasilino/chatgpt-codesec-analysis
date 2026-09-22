#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int max_sum_triangle(int** triangle, int num_rows) {
    if (triangle == NULL || num_rows <= 0) {
        return 0;
    }

    int** dp = (int**)malloc(num_rows * sizeof(int*));
    if (dp == NULL) {
        return 0;
    }

    for (int i = 0; i < num_rows; i++) {
        dp[i] = (int*)malloc((i + 1) * sizeof(int));
        if (dp[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(dp[j]);
            }
            free(dp);
            return 0;
        }
    }

    dp[0][0] = triangle[0][0];

    for (int i = 1; i < num_rows; i++) {
        dp[i][0] = dp[i - 1][0] + triangle[i][0];
        
        for (int j = 1; j < i; j++) {
            dp[i][j] = MAX(dp[i - 1][j - 1], dp[i - 1][j]) + triangle[i][j];
        }
        
        dp[i][i] = dp[i - 1][i - 1] + triangle[i][i];
    }

    int max_sum = dp[num_rows - 1][0];
    for (int i = 1; i < num_rows; i++) {
        max_sum = MAX(max_sum, dp[num_rows - 1][i]);
    }

    for (int i = 0; i < num_rows; i++) {
        free(dp[i]);
    }
    free(dp);

    return max_sum;
}

int main(void) {
    int num_rows = 4;
    
    int** triangle = (int**)malloc(num_rows * sizeof(int*));
    if (triangle == NULL) {
        return 1;
    }

    for (int i = 0; i < num_rows; i++) {
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
    
    triangle[1][0] = 7;
    triangle[1][1] = 4;
    
    triangle[2][0] = 2;
    triangle[2][1] = 4;
    triangle[2][2] = 6;
    
    triangle[3][0] = 8;
    triangle[3][1] = 5;
    triangle[3][2] = 9;
    triangle[3][3] = 3;

    int result = max_sum_triangle(triangle, num_rows);
    printf("Maximum sum: %d\n", result);

    for (int i = 0; i < num_rows; i++) {
        free(triangle[i]);
    }
    free(triangle);

    return 0;
}