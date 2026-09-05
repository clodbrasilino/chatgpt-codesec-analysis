#include <stdio.h>
#include <stdlib.h>

int min(int x, int y, int z) {
    if (x < y) {
        return (x < z) ? x : z;
    } else {
        return (y < z) ? y : z;
    }
}

int determineCost(int **cost, int m, int n, int **tc, int *result) {
    if (!cost || !tc || !result || m < 0 || n < 0) {
        return -1;
    }

    tc[0][0] = cost[0][0];

    for (int i = 1; i <= m; i++) {
        tc[i][0] = tc[i - 1][0] + cost[i][0];
    }

    for (int j = 1; j <= n; j++) {
        tc[0][j] = tc[0][j - 1] + cost[0][j];
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            tc[i][j] = min(tc[i - 1][j - 1], tc[i - 1][j], tc[i][j - 1]) + cost[i][j];
        }
    }

    *result = tc[m][n];
    return 0;
}

int minCost(int **cost, int m, int n, int *result) {
    if (!cost || m < 0 || n < 0 || !result) {
        return -1;
    }

    int **tc = (int **)malloc((m + 1) * sizeof(int *));
    if (!tc) {
        return -1;
    }

    for (int i = 0; i <= m; i++) {
        tc[i] = (int *)malloc((n + 1) * sizeof(int));
        if (!tc[i]) {
            for (int j = 0; j < i; j++) {
                free(tc[j]);
            }
            free(tc);
            return -1;
        }
    }

    int status = determineCost(cost, m, n, tc, result);

    for (int i = 0; i <= m; i++) {
        free(tc[i]);
    }
    free(tc);

    return status;
}

int main(void) {
    int m = 2;
    int n = 2;
    int rows = 3;
    int cols = 3;

    int **cost = (int **)malloc(rows * sizeof(int *));
    if (!cost) {
        return 1;
    }

    for (int i = 0; i < rows; i++) {
        cost[i] = (int *)malloc(cols * sizeof(int));
        if (!cost[i]) {
            for (int j = 0; j < i; j++) {
                free(cost[j]);
            }
            free(cost);
            return 1;
        }
    }

    int initial_cost[3][3] = {
        {1, 2, 3},
        {4, 8, 2},
        {1, 5, 3}
    };

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cost[i][j] = initial_cost[i][j];
        }
    }

    int result = 0;
    int status = minCost(cost, m, n, &result);

    if (status == 0) {
        printf("%d\n", result);
    }

    for (int i = 0; i < rows; i++) {
        free(cost[i]);
    }
    free(cost);

    return (status == 0) ? 0 : 1;
}