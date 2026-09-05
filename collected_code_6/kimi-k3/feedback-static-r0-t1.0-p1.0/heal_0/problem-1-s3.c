#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int min(int x, int y, int z) {
    if (x < y) {
        return (x < z) ? x : z;
    } else {
        return (y < z) ? y : z;
    }
}

int minCost(int **cost, int m, int n) {
    int **tc;
    int i, j;
    
    tc = (int **)malloc((m + 1) * sizeof(int *));
    if (tc == NULL) {
        return -1;
    }
    
    for (i = 0; i <= m; i++) {
        tc[i] = (int *)malloc((n + 1) * sizeof(int));
        if (tc[i] == NULL) {
            for (j = 0; j < i; j++) {
                free(tc[j]);
            }
            free(tc);
            return -1;
        }
    }
    
    tc[0][0] = cost[0][0];
    
    for (j = 1; j <= n; j++) {
        tc[0][j] = tc[0][j - 1] + cost[0][j];
    }
    
    for (i = 1; i <= m; i++) {
        tc[i][0] = tc[i - 1][0] + cost[i][0];
    }
    
    for (i = 1; i <= m; i++) {
        for (j = 1; j <= n; j++) {
            tc[i][j] = min(tc[i - 1][j - 1], tc[i - 1][j], tc[i][j - 1]) + cost[i][j];
        }
    }
    
    int result = tc[m][n];
    
    for (i = 0; i <= m; i++) {
        free(tc[i]);
    }
    free(tc);
    
    return result;
}

int main() {
    int m, n, i, j;
    int **cost;
    int result;
    
    if (scanf("%d %d", &m, &n) != 2) {
        return 1;
    }
    
    if (m < 0 || n < 0) {
        return 1;
    }
    
    cost = (int **)malloc((m + 1) * sizeof(int *));
    if (cost == NULL) {
        return 1;
    }
    
    for (i = 0; i <= m; i++) {
        cost[i] = (int *)malloc((n + 1) * sizeof(int));
        if (cost[i] == NULL) {
            for (j = 0; j < i; j++) {
                free(cost[j]);
            }
            free(cost);
            return 1;
        }
    }
    
    for (i = 0; i <= m; i++) {
        for (j = 0; j <= n; j++) {
            if (scanf("%d", &cost[i][j]) != 1) {
                for (int k = 0; k <= m; k++) {
                    free(cost[k]);
                }
                free(cost);
                return 1;
            }
        }
    }
    
    result = minCost(cost, m, n);
    
    if (result != -1) {
        printf("%d\n", result);
    }
    
    for (i = 0; i <= m; i++) {
        free(cost[i]);
    }
    free(cost);
    
    return 0;
}