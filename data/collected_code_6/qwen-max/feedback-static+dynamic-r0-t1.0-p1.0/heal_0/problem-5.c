#include <stdio.h>

int countWays(int n) {
    if (n == 0)
        return 1;
    if (n == 1)
        return 3;
    int dp[n + 1];
    dp[0] = 1;
    dp[1] = 3;
    for (int i = 2; i <= n; ++i) {
        dp[i] = 2 * dp[i - 1] + 2 * dp[i - 2];
    }
    return dp[n];
}

int main() {
    int n = 2;
    printf("%d\n", countWays(n));
    return 0;
}