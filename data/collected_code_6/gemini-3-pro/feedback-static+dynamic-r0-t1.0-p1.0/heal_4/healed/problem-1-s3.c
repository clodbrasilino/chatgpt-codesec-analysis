#include <stdio.h>
#include <stdlib.h>

int min(int x, int y, int z) {
    if (x < y)
        return (x < z) ? x : z;
    else
        return (y < z) ? y : z;
}

int minCost(int** cost, int m, int n) {
    if (m < 0 || n < 0) return 0;

    int** tc = (int**)malloc((m + 1) * sizeof(int*));
    if (!tc) return 0;

    for (int i = 0; i <= m; i++) {
        tc[i] = (int*)malloc((n + 1) * sizeof(int));
        if (!tc[i]) {
            for (int k = 0; k < i; k++) {
                free(tc[k]);
            }
            free(tc);
            return 0;
        }
    }

    tc[0][0] = cost[0][0];

    for (int i = 1; i <= m; i++)
        tc[i][0] = tc[i - 1][0] + cost[i][0];

    for (int j = 1; j <= n; j++)
        tc[0][j] = tc[0][j - 1] + cost[0][j];

    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            tc[i][j] = min(tc[i - 1][j - 1], tc[i - 1][j], tc[i][j - 1]) + cost[i][j];

    int result = tc[m][n];

    for (int i = 0; i <= m; i++)
        free(tc[i]);
    free(tc);

    return result;
}

int main() {
    int row_m, col_n;
    if (scanf("%d %d", &row_m, &col_n) != 2) return 0;
    if (row_m <= 0 || col_n <= 0) return 0;

    int** cost = (int**)malloc(row_m * sizeof(int*));
    if (!cost) return 0;

    for (int i = 0; i < row_m; i++) {
        cost[i] = (int*)malloc(col_n * sizeof(int));
        if (!cost[i]) {
            for (int k = 0; k < i; k++) {
                free(cost[k]);
            }
            free(cost);
            return 0;
        }
        for (int j = 0; j < col_n; j++) {
            if (scanf("%d", &cost[i][j]) != 1) {
                cost[i][j] = 0; 
            }
        }
    }

    int m, n;
    if (scanf("%d %d", &m, &n) == 2) {
        if (m < 0 || m >= row_m || n < 0 || n >= col_n) {
            m = row_m - 1;
            n = col_n - 1;
        }
    } else {
        m = row_m - 1;
        n = col_n - 1;
    }

    printf("%d\n", minCost(cost, m, n));

    for (int i = 0; i < row_m; i++)
        free(cost[i]);
    free(cost);

    return 0;
}