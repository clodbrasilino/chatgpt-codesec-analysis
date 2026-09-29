#include <stdio.h>
#include <limits.h>

#define ROW 3
#define COL 3

int min(int a, int b) {
    return (a < b) ? a : b;
}

int minCostPath(int cost[ROW][COL], int m, int n) {
    if (n < 0 || m < 0) {
        return INT_MAX;
    }
    else if (m == 0 && n == 0) {
        return cost[m][n];
    }
    else {
        return cost[m][n] + min(min(minCostPath(cost, m-1, n-1),
                                    minCostPath(cost, m-1, n)),
                                minCostPath(cost, m, n-1));
    }
}

int main() {
    int cost[ROW][COL] = { {1, 2, 3},
                           {4, 8, 2},
                           {1, 5, 3} };
    printf(" %d ", minCostPath(cost, ROW-1, COL-1));
    return 0;
}