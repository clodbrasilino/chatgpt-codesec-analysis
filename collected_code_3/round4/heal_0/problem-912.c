#include <stdio.h>

int lobb(int n, int m) {
    if (n == 0 || m == 0)
        return 1;
    if (n < 0 || m < 0)
        return 0;
    int dp[n + 2][2 * m + 2];
    for (int i = 0; i <= n + 1; i++)
        for (int j = 0; j <= 2 * m + 1; j++)
            dp[i][j] = 0;
    dp[0][m] = 1;
    for (int i = 1; i <= n + 1; i++)
        for (int j = 0; j <= 2 * m; j++)
            if (j > 0)
                dp[i][j] = dp[i - 1][j - 1] + dp[i][j - 1];
            else
                dp[i][j] = dp[i - 1][j];
    return dp[n + 1][0];
}

int main() {
    int n, m;
    printf("Enter n: ");
    scanf("%d", &n);
    printf("Enter m: ");
    scanf("%d", &m);
    printf("Lobb Number is: %d\n", lobb(n, m));
    return 0;
}