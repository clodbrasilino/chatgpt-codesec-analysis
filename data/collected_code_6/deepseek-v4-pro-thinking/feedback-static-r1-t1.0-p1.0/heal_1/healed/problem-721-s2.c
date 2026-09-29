#include <stdio.h>
#include <stdlib.h>

int findMaxAveragePath(int n, int matrix[n][n], int pathRows[], int pathCols[], int *pathLength, double *average) {
    if (n <= 0 || matrix == NULL || pathRows == NULL || pathCols == NULL || pathLength == NULL || average == NULL) {
        return -1;
    }

    long long **dp = malloc((size_t)n * sizeof(*dp));
    if (dp == NULL) {
        return -1;
    }

    for (int i = 0; i < n; i++) {
        dp[i] = malloc((size_t)n * sizeof(*dp[i]));
        if (dp[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(dp[j]);
            }
            free(dp);
            return -1;
        }
    }

    dp[0][0] = matrix[0][0];

    for (int j = 1; j < n; j++) {
        dp[0][j] = dp[0][j - 1] + matrix[0][j];
    }

    for (int i = 1; i < n; i++) {
        dp[i][0] = dp[i - 1][0] + matrix[i][0];
        for (int j = 1; j < n; j++) {
            long long fromTop = dp[i - 1][j];
            long long fromLeft = dp[i][j - 1];
            dp[i][j] = matrix[i][j] + (fromTop > fromLeft ? fromTop : fromLeft);
        }
    }

    int length = 2 * n - 1;
    int row = n - 1;
    int col = row;

    for (int k = length - 1; k >= 0; k--) {
        pathRows[k] = row;
        pathCols[k] = col;

        if (row == 0 && col == 0) {
            break;
        }

        if (row == 0) {
            col--;
        } else if (col == 0) {
            row--;
        } else if (dp[row - 1][col] > dp[row][col - 1]) {
            row--;
        } else {
            col--;
        }
    }

    *pathLength = length;
    *average = (double)dp[n - 1][n - 1] / length;

    for (int i = 0; i < n; i++) {
        free(dp[i]);
    }
    free(dp);

    return 0;
}

int main(void) {
    int n;

    if (scanf("%d", &n) != 1 || n <= 0) {
        return 1;
    }

    int (*matrix)[n] = malloc((size_t)n * sizeof(*matrix));
    if (matrix == NULL) {
        return 1;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (scanf("%d", &matrix[i][j]) != 1) {
                free(matrix);
                return 1;
            }
        }
    }

    int pathLength = 0;
    int *pathRows = malloc((size_t)(2 * n - 1) * sizeof(*pathRows));
    int *pathCols = malloc((size_t)(2 * n - 1) * sizeof(*pathCols));

    if (pathRows == NULL || pathCols == NULL) {
        free(pathRows);
        free(pathCols);
        free(matrix);
        return 1;
    }

    double average = 0.0;

    if (findMaxAveragePath(n, matrix, pathRows, pathCols, &pathLength, &average) != 0) {
        free(pathRows);
        free(pathCols);
        free(matrix);
        return 1;
    }

    printf("%.6f\n", average);

    for (int i = 0; i < pathLength; i++) {
        printf("(%d,%d)", pathRows[i], pathCols[i]);
        if (i < pathLength - 1) {
            printf(" ");
        }
    }
    printf("\n");

    free(pathRows);
    free(pathCols);
    free(matrix);

    return 0;
}