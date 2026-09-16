#include <stdio.h>
#include <stdlib.h>

int maxTriangleSum(int **triangle, int n)
{
    int i;
    int j;
    int *dp;
    int result;

    dp = malloc((size_t)n * sizeof(int));
    if (dp == NULL) {
        return -1;
    }

    for (j = 0; j < n; j++) {
        dp[j] = triangle[n - 1][j];
    }

    for (i = n - 2; i >= 0; i--) {
        for (j = 0; j <= i; j++) {
            if (dp[j] > dp[j + 1]) {
                dp[j] = triangle[i][j] + dp[j];
            } else {
                dp[j] = triangle[i][j] + dp[j + 1];
            }
        }
    }

    result = dp[0];
    free(dp);
    return result;
}

int main(void)
{
    int n;
    int i;
    int j;
    int **triangle;
    int result;

    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input for number of rows\n");
        return EXIT_FAILURE;
    }

    triangle = malloc((size_t)n * sizeof(int *));
    if (triangle == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < n; i++) {
        triangle[i] = malloc((size_t)(i + 1) * sizeof(int));
        if (triangle[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            for (j = 0; j < i; j++) {
                free(triangle[j]);
            }
            free(triangle);
            return EXIT_FAILURE;
        }
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j <= i; j++) {
            if (scanf("%d", &triangle[i][j]) != 1) {
                fprintf(stderr, "Invalid input for triangle element\n");
                for (j = 0; j < n; j++) {
                    free(triangle[j]);
                }
                free(triangle);
                return EXIT_FAILURE;
            }
        }
    }

    result = maxTriangleSum(triangle, n);

    for (i = 0; i < n; i++) {
        free(triangle[i]);
    }
    free(triangle);

    if (result < 0) {
        fprintf(stderr, "Computation failed\n");
        return EXIT_FAILURE;
    }

    printf("Maximum sum: %d\n", result);
    return EXIT_SUCCESS;
}