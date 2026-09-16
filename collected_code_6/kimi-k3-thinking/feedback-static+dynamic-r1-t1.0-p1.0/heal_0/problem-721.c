#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <float.h>

static double findMaxAveragePath(const int *matrix, size_t n)
{
    size_t i;
    size_t j;
    double up;
    double left;
    double maxSum;
    double *dp;

    if (matrix == NULL || n == 0 || n > SIZE_MAX / n ||
        (n * n) > (SIZE_MAX / sizeof(*dp)))
    {
        return -DBL_MAX;
    }

    dp = (double *)malloc(n * n * sizeof(*dp));
    if (dp == NULL)
    {
        return -DBL_MAX;
    }

    dp[0] = (double)matrix[0];

    for (j = 1; j < n; j++)
    {
        dp[j] = dp[j - 1] + (double)matrix[j];
    }

    for (i = 1; i < n; i++)
    {
        dp[i * n] = dp[(i - 1) * n] + (double)matrix[i * n];
        for (j = 1; j < n; j++)
        {
            up = dp[(i - 1) * n + j];
            left = dp[i * n + (j - 1)];
            dp[i * n + j] = ((up > left) ? up : left) + (double)matrix[i * n + j];
        }
    }

    maxSum = dp[(n - 1) * n + (n - 1)];

    free(dp);
    dp = NULL;

    return maxSum / (double)(2 * n - 1);
}

int main(void)
{
    const size_t n = 4;
    const int sample[16] = {
        1, 2, 3, 4,
        6, 1, 2, 4,
        5, 7, 9, 2,
        1, 3, 8, 5
    };
    size_t i;
    int *matrix;
    double maxAverage;

    matrix = (int *)malloc(n * n * sizeof(*matrix));
    if (matrix == NULL)
    {
        fprintf(stderr, "Error: memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < n * n; i++)
    {
        matrix[i] = sample[i];
    }

    maxAverage = findMaxAveragePath(matrix, n);

    free(matrix);
    matrix = NULL;

    if (maxAverage == -DBL_MAX)
    {
        fprintf(stderr, "Error: unable to compute the maximum average path.\n");
        return EXIT_FAILURE;
    }

    printf("Maximum average over all paths: %.4f\n", maxAverage);

    return EXIT_SUCCESS;
}