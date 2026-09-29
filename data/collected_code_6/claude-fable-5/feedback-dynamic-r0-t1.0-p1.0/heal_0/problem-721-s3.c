#include <stdio.h>
#include <stdlib.h>

double maxAveragePath(const int *matrix, size_t n)
{
    size_t i;
    size_t j;
    long long *dp;
    double result;

    if (matrix == NULL || n == 0U) {
        return 0.0;
    }

    dp = (long long *)malloc(n * n * sizeof(long long));
    if (dp == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    dp[0] = (long long)matrix[0];

    for (j = 1U; j < n; j++) {
        dp[j] = dp[j - 1U] + (long long)matrix[j];
    }

    for (i = 1U; i < n; i++) {
        dp[i * n] = dp[(i - 1U) * n] + (long long)matrix[i * n];
        for (j = 1U; j < n; j++) {
            long long fromTop = dp[(i - 1U) * n + j];
            long long fromLeft = dp[i * n + (j - 1U)];
            long long best = (fromTop > fromLeft) ? fromTop : fromLeft;
            dp[i * n + j] = best + (long long)matrix[i * n + j];
        }
    }

    result = (double)dp[n * n - 1U] / (double)(2U * n - 1U);

    free(dp);

    return result;
}

int main(void)
{
    size_t n;
    size_t i;
    size_t j;
    int *matrix;
    double answer;

    printf("Enter matrix size n: ");
    if (scanf("%zu", &n) != 1) {
        fprintf(stderr, "Invalid input for size\n");
        return EXIT_FAILURE;
    }

    if (n == 0U || n > 1000U) {
        fprintf(stderr, "Size out of allowed range\n");
        return EXIT_FAILURE;
    }

    matrix = (int *)malloc(n * n * sizeof(int));
    if (matrix == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Enter %zu matrix elements:\n", n * n);
    for (i = 0U; i < n; i++) {
        for (j = 0U; j < n; j++) {
            if (scanf("%d", &matrix[i * n + j]) != 1) {
                fprintf(stderr, "Invalid matrix element\n");
                free(matrix);
                return EXIT_FAILURE;
            }
        }
    }

    answer = maxAveragePath(matrix, n);
    printf("Maximum average path value: %f\n", answer);

    free(matrix);

    return EXIT_SUCCESS;
}