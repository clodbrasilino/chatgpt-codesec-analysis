#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>

#define MAX_SIZE 100

static int64_t min(int64_t x, int64_t y, int64_t z) {
    int64_t m = x < y ? x : y;
    return m < z ? m : z;
}

static int minCost(int cost[MAX_SIZE][MAX_SIZE], int m, int n) {
    if (m < 0 || n < 0 || m >= MAX_SIZE || n >= MAX_SIZE) {
        return -1;
    }

    int64_t tc[MAX_SIZE][MAX_SIZE];

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            tc[i][j] = 0;
        }
    }

    tc[0][0] = cost[0][0];

    for (int i = 1; i <= m; i++) {
        tc[i][0] = tc[i - 1][0] + cost[i][0];
        if (tc[i][0] > INT_MAX) {
            return -1;
        }
    }

    for (int j = 1; j <= n; j++) {
        tc[0][j] = tc[0][j - 1] + cost[0][j];
        if (tc[0][j] > INT_MAX) {
            return -1;
        }
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            int64_t min_val = min(tc[i - 1][j - 1], tc[i - 1][j], tc[i][j - 1]);
            tc[i][j] = min_val + cost[i][j];
            if (tc[i][j] > INT_MAX) {
                return -1;
            }
        }
    }

    return (int)tc[m][n];
}

int main(void) {
    int cost[MAX_SIZE][MAX_SIZE];
    int m, n;
    int result;

    if (scanf("%d %d", &m, &n) != 2) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    if (m <= 0 || n <= 0 || m > MAX_SIZE || n > MAX_SIZE) {
        fprintf(stderr, "Invalid dimensions\n");
        return 1;
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (scanf("%d", &cost[i][j]) != 1) {
                fprintf(stderr, "Invalid input\n");
                return 1;
            }
        }
    }

    result = minCost(cost, m - 1, n - 1);
    if (result != -1) {
        printf("%d\n", result);
    } else {
        fprintf(stderr, "Error in calculation\n");
        return 1;
    }

    return 0;
}