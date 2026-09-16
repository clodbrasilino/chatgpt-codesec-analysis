#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int min(int a, int b) {
    return (a < b) ? a : b;
}

int minCostPath(int **cost, int m, int n) {
    if (m < 0 || n < 0)
        return INT_MAX;
    if (m == 0 && n == 0)
        return cost[0][0];

    int up = minCostPath(cost, m - 1, n);
    int left = minCostPath(cost, m, n - 1);

    if (up == INT_MAX && left == INT_MAX)
        return INT_MAX;

    return cost[m][n] + min(up, left);
}

int main(void) {
    int rows, cols;

    printf("Enter number of rows: ");
    if (scanf("%d", &rows) != 1 || rows <= 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    printf("Enter number of columns: ");
    if (scanf("%d", &cols) != 1 || cols <= 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    int **cost = (int **)malloc(rows * sizeof(int *));
    if (cost == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < rows; i++) {
        cost[i] = (int *)malloc(cols * sizeof(int));
        if (cost[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(cost[j]);
            }
            free(cost);
            fprintf(stderr, "Memory allocation failed\n");
            return EXIT_FAILURE;
        }
    }

    printf("Enter the cost matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (scanf("%d", &cost[i][j]) != 1) {
                for (int k = 0; k < rows; k++) {
                    free(cost[k]);
                }
                free(cost);
                fprintf(stderr, "Invalid input\n");
                return EXIT_FAILURE;
            }
        }
    }

    int m, n;
    printf("Enter destination position (m n): ");
    if (scanf("%d %d", &m, &n) != 2 || m < 0 || n < 0 || m >= rows || n >= cols) {
        for (int i = 0; i < rows; i++) {
            free(cost[i]);
        }
        free(cost);
        fprintf(stderr, "Invalid destination\n");
        return EXIT_FAILURE;
    }

    int result = minCostPath(cost, m, n);
    if (result == INT_MAX) {
        fprintf(stderr, "Path not reachable\n");
        for (int i = 0; i < rows; i++) {
            free(cost[i]);
        }
        free(cost);
        return EXIT_FAILURE;
    }

    printf("Minimum cost path: %d\n", result);

    for (int i = 0; i < rows; i++) {
        free(cost[i]);
    }
    free(cost);

    return EXIT_SUCCESS;
}