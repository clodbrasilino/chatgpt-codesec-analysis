#include <stdio.h>
#include <stdlib.h>
#include <float.h>

void findMaxAveragePath(int **matrix, int n, int *path, double *maxAvg) {
    double **dp = (double **)malloc(n * sizeof(double *));
    int **parent = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        dp[i] = (double *)malloc(n * sizeof(double));
        parent[i] = (int *)malloc(n * sizeof(int));
    }

    dp[0][0] = matrix[0][0];
    parent[0][0] = -1;

    for (int j = 1; j < n; j++) {
        dp[0][j] = dp[0][j-1] + matrix[0][j];
        parent[0][j] = 0;
    }

    for (int i = 1; i < n; i++) {
        dp[i][0] = dp[i-1][0] + matrix[i][0];
        parent[i][0] = 1;
    }

    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            if (dp[i-1][j] > dp[i][j-1]) {
                dp[i][j] = dp[i-1][j] + matrix[i][j];
                parent[i][j] = 1;
            } else {
                dp[i][j] = dp[i][j-1] + matrix[i][j];
                parent[i][j] = 0;
            }
        }
    }

    *maxAvg = dp[n-1][n-1] / (2 * n - 1);

    int i = n - 1, j = n - 1;
    int pathLength = 2 * n - 1;
    for (int k = pathLength - 1; k >= 0; k--) {
        path[k] = matrix[i][j];
        if (parent[i][j] == 1) {
            i--;
        } else if (parent[i][j] == 0) {
            j--;
        } else {
            break;
        }
    }

    for (int i = 0; i < n; i++) {
        free(dp[i]);
        free(parent[i]);
    }
    free(dp);
    free(parent);
}

int main() {
    int n;
    printf("Enter matrix size: ");
    scanf("%d", &n);

    int **matrix = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int *)malloc(n * sizeof(int));
    }

    printf("Enter matrix elements:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    int *path = (int *)malloc((2 * n - 1) * sizeof(int));
    double maxAvg;

    findMaxAveragePath(matrix, n, path, &maxAvg);

    printf("Maximum average path: ");
    for (int i = 0; i < 2 * n - 1; i++) {
        printf("%d ", path[i]);
    }
    printf("\nMaximum average: %.2f\n", maxAvg);

    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
    free(path);

    return 0;
}