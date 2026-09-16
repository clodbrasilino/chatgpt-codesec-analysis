#include <stdio.h>
#include <stdlib.h>

static int maxAveragePath(const int *matrix, int n, int *pathRow, int *pathCol, double *outAverage)
{
    double *dp;
    double maxSum;
    int i;
    int j;
    int idx;

    if (matrix == NULL || pathRow == NULL || pathCol == NULL || outAverage == NULL || n <= 0)
    {
        return -1;
    }

    dp = (double *)malloc((size_t)n * (size_t)n * sizeof(double));
    if (dp == NULL)
    {
        return -1;
    }

    dp[0] = (double)matrix[0];
    for (j = 1; j < n; j++)
    {
        dp[j] = dp[j - 1] + (double)matrix[j];
    }
    for (i = 1; i < n; i++)
    {
        dp[(size_t)i * (size_t)n] = dp[(size_t)(i - 1) * (size_t)n] + (double)matrix[(size_t)i * (size_t)n];
        for (j = 1; j < n; j++)
        {
            double fromTop = dp[(size_t)(i - 1) * (size_t)n + (size_t)j];
            double fromLeft = dp[(size_t)i * (size_t)n + (size_t)(j - 1)];
            dp[(size_t)i * (size_t)n + (size_t)j] =
                (fromTop > fromLeft ? fromTop : fromLeft) + (double)matrix[(size_t)i * (size_t)n + (size_t)j];
        }
    }

    maxSum = dp[(size_t)n * (size_t)n - 1u];

    i = n - 1;
    j = n - 1;
    for (idx = 2 * n - 2; idx >= 0; idx--)
    {
        pathRow[idx] = i;
        pathCol[idx] = j;
        if (i > 0 && j > 0)
        {
            if (dp[(size_t)(i - 1) * (size_t)n + (size_t)j] >= dp[(size_t)i * (size_t)n + (size_t)(j - 1)])
            {
                i--;
            }
            else
            {
                j--;
            }
        }
        else if (i > 0)
        {
            i--;
        }
        else
        {
            j--;
        }
    }

    free(dp);
    dp = NULL;

    *outAverage = maxSum / (double)(2 * n - 1);
    return 0;
}

int main(void)
{
    static const int values[16] = {
        1, 2, 3, 4,
        6, 5, 4, 8,
        7, 1, 9, 2,
        8, 3, 1, 10
    };
    const int n = 4;
    int *matrix = NULL;
    int *pathRow = NULL;
    int *pathCol = NULL;
    double maxAvg = 0.0;
    int i;

    matrix = (int *)malloc((size_t)n * (size_t)n * sizeof(int));
    pathRow = (int *)malloc((size_t)(2 * n - 1) * sizeof(int));
    pathCol = (int *)malloc((size_t)(2 * n - 1) * sizeof(int));

    if (matrix == NULL || pathRow == NULL || pathCol == NULL)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        free(matrix);
        free(pathRow);
        free(pathCol);
        return EXIT_FAILURE;
    }

    for (i = 0; i < n * n; i++)
    {
        matrix[i] = values[i];
    }

    if (maxAveragePath(matrix, n, pathRow, pathCol, &maxAvg) != 0)
    {
        fprintf(stderr, "Failed to compute the path.\n");
        free(matrix);
        free(pathRow);
        free(pathCol);
        return EXIT_FAILURE;
    }

    printf("Matrix:\n");
    for (i = 0; i < n * n; i++)
    {
        printf("%4d", matrix[i]);
        if ((i + 1) % n == 0)
        {
            printf("\n");
        }
    }

    printf("Maximum average: %.4f\n", maxAvg);
    printf("Path values:");
    for (i = 0; i < 2 * n - 1; i++)
    {
        printf(" %d", matrix[pathRow[i] * n + pathCol[i]]);
    }
    printf("\nPath coordinates:");
    for (i = 0; i < 2 * n - 1; i++)
    {
        printf(" (%d,%d)", pathRow[i], pathCol[i]);
    }
    printf("\n");

    free(matrix);
    free(pathRow);
    free(pathCol);
    matrix = NULL;
    pathRow = NULL;
    pathCol = NULL;

    return EXIT_SUCCESS;
}