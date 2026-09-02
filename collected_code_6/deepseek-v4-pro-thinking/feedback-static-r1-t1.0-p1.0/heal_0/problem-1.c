#include <stdio.h>

#define MAX 100

int min3(int a, int b, int c)
{
    int min = a;

    if (b < min) {
        min = b;
    }
    if (c < min) {
        min = c;
    }

    return min;
}

int minCostPath(int cost[][MAX], int m, int n)
{
    int dp[MAX][MAX];
    int i, j;

    if (m < 0 || n < 0 || m >= MAX || n >= MAX) {
        return -1;
    }

    dp[0][0] = cost[0][0];

    for (i = 1; i <= m; i++) {
        dp[i][0] = dp[i - 1][0] + cost[i][0];
    }

    for (j = 1; j <= n; j++) {
        dp[0][j] = dp[0][j - 1] + cost[0][j];
    }

    for (i = 1; i <= m; i++) {
        for (j = 1; j <= n; j++) {
            dp[i][j] = cost[i][j] + min3(dp[i - 1][j - 1],
                                         dp[i - 1][j],
                                         dp[i][j - 1]);
        }
    }

    return dp[m][n];
}

int main(void)
{
    int cost[MAX][MAX];
    int m, n;
    int i, j;

    if (scanf("%d %d", &m, &n) != 2) {
        return 1;
    }

    if (m < 0 || n < 0 || m >= MAX || n >= MAX) {
        return 1;
    }

    for (i = 0; i <= m; i++) {
        for (j = 0; j <= n; j++) {
            if (scanf("%d", &cost[i][j]) != 1) {
                return 1;
            }
        }
    }

    printf("%d\n", minCostPath(cost, m, n));

    return 0;
}