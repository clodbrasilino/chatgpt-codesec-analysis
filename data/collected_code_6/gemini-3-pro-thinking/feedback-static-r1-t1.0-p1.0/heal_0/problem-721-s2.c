#include <stdio.h>
#include <stdlib.h>

double findMaxAveragePath(int **matrix, int n);

double findMaxAveragePath(int **matrix, int n) {
    if (matrix == NULL || n <= 0) {
        return 0.0;
    }

    int *dp = (int *)malloc((size_t)n * sizeof(int));
    if (dp == NULL) {
        return 0.0;
    }

    dp[0] = matrix[0][0];
    for (int j = 1; j < n; j++) {
        dp[j] = dp[j - 1] + matrix[0][j];
    }

    for (int i = 1; i < n; i++) {
        dp[0] = dp[0] + matrix[i][0];
        for (int j = 1; j < n; j++) {
            int from_top = dp[j];
            int from_left = dp[j - 1];
            dp[j] = matrix[i][j] + (from_top > from_left ? from_top : from_left);
        }
    }

    int max_sum = dp[n - 1];
    int path_length = 2 * n - 1;
    double max_avg = (double)max_sum / path_length;

    free(dp);

    return max_avg;
}

int main(void) {
    int n = 3;
    
    int **matrix = (int **)malloc((size_t)n * sizeof(int *));
    if (matrix == NULL) {
        return EXIT_FAILURE;
    }

    for (int i = 0; i < n; i++) {
        matrix[i] = (int *)malloc((size_t)n * sizeof(int));
        if (matrix[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            return EXIT_FAILURE;
        }
    }

    matrix[0][0] = 1;
    matrix[0][1] = 2;
    matrix[0][2] = 3;
    matrix[1][0] = 4;
    matrix[1][1] = 5;
    matrix[1][2] = 6;
    matrix[2][0] = 7;
    matrix[2][1] = 8;
    matrix[2][2] = 9;

    double result = findMaxAveragePath(matrix, n);
    printf("%f\n", result);

    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return EXIT_SUCCESS;
}