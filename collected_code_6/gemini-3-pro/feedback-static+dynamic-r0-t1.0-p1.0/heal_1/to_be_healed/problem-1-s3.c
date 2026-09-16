#include <stdio.h>
#include <stdlib.h>

int min(int x, int y, int z) {
    if (x < y)
        return (x < z) ? x : z;
    else
        return (y < z) ? y : z;
}
 /* Possible weaknesses found:
  *  test case 0 failed: expected 8, got -1
  *  test case 1 failed: expected 12, got -1
  *  test case 2 failed: expected 16, got -1
  */

int minCost(int** cost, int m, int n, int row_m, int col_n) {
    if (cost == NULL || m < 0 || n < 0 || m >= row_m || n >= col_n) {
        return -1;
    }

    int** tc = (int**)malloc(row_m * sizeof(int*));
    if (tc == NULL) {
        return -1;
    }
    for (int i = 0; i < row_m; i++) {
        tc[i] = (int*)malloc(col_n * sizeof(int));
        if (tc[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(tc[j]);
            }
            free(tc);
            return -1;
        }
    }

    tc[0][0] = cost[0][0];

    for (int i = 1; i <= m; i++)
        tc[i][0] = tc[i - 1][0] + cost[i][0];

    for (int j = 1; j <= n; j++)
        tc[0][j] = tc[0][j - 1] + cost[0][j];

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            tc[i][j] = min(tc[i - 1][j - 1], tc[i - 1][j], tc[i][j - 1]) + cost[i][j];
        }
    }

    int result = tc[m][n];

    for (int i = 0; i < row_m; i++) {
        free(tc[i]);
    }
    free(tc);

    return result;
}

int main() {
    int row_m = 3;
    int col_n = 3;

    int** cost = (int**)malloc(row_m * sizeof(int*));
    if (cost == NULL) {
        return 1;
    }
    for (int i = 0; i < row_m; i++) {
        cost[i] = (int*)malloc(col_n * sizeof(int));
        if (cost[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(cost[j]);
            }
            free(cost);
            return 1;
        }
    }

    cost[0][0] = 1; cost[0][1] = 2; cost[0][2] = 3;
    cost[1][0] = 4; cost[1][1] = 8; cost[1][2] = 2;
    cost[2][0] = 1; cost[2][1] = 5; cost[2][2] = 3;

    int m = 2;
    int n = 2;

    int result = minCost(cost, m, n, row_m, col_n);
    if (result != -1) {
        printf("%d\n", result);
    } else {
        printf("Error\n");
    }

    for (int i = 0; i < row_m; i++) {
        free(cost[i]);
    }
    free(cost);

    return 0;
}