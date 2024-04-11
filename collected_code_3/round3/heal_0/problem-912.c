#include <stdio.h>

int lobb(int n, int m) {
    if (n == 0 || m == 0)
        return 1;
    if (n < 0 || m < 0)
        return 0;
    int dp[n + 2][m + 1][n + m + 1];
    for (int i = 0; i <= n + 1; i++)
        for (int j = 0; j <= m; j++)
            for (int k = 0; k <= n + m; k++)
                dp[i][j][k] = 0;
    dp[1][0][0] = 1;
    for (int i = 1; i <= n + 1; i++)
        for (int j = 0; j <= m; j++)
            for (int k = 0; k <= n + m; k++) {
                if (j < m)
                    dp[i][j + 1][k + 1] += dp[i][j][k];
                if (i < n + 1)
                    dp[i + 1][j][k + 1] += dp[i][j][k];
                if (k < n + m && 2 * k > i + j)
                    dp[i][j][k + 1] -= dp[i][j][k];
            }
    return dp[n + 1][m][n + m];
}

int main() {
    int n, m;
    printf("Enter the values of n and m: ");
    scanf("%d %d", &n, &m);
    printf("The Lobb number is: %d\n", lobb(n, m));
    return 0;
}