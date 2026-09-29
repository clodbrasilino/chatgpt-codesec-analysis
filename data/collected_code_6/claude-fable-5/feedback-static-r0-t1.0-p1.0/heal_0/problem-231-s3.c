#include <stdio.h>
#include <stdlib.h>

int max_triangle_sum(int **triangle, int rows)
{
    int i;
    int j;
    int result;
    int *dp;

    dp = malloc((size_t)rows * sizeof(int));
    if (dp == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    for (j = 0; j < rows; j++) {
        dp[j] = triangle[rows - 1][j];
    }

    for (i = rows - 2; i >= 0; i--) {
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

    printf("Enter number of rows: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input\n");
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

    printf("Enter triangle values row by row:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j <= i; j++) {
            if (scanf("%d", &triangle[i][j]) != 1) {
                fprintf(stderr, "Invalid input\n");
                for (j = 0; j < n; j++) {
                    free(triangle[j]);
                }
                free(triangle);
                return EXIT_FAILURE;
            }
        }
    }

    result = max_triangle_sum(triangle, n);
    printf("Maximum sum: %d\n", result);

    for (i = 0; i < n; i++) {
        free(triangle[i]);
    }
    free(triangle);

    return EXIT_SUCCESS;
}