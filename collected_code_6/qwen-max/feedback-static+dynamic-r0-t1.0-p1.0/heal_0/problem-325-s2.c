#include <stdio.h>
#include <limits.h>

int minSquares(int n) {
    int dp[n + 1];
    dp[0] = 0;
    for (int i = 1; i <= n; ++i) {
        dp[i] = INT_MAX;
        for (int x = 1; x * x <= i; ++x)
            if (dp[i - x * x] != INT_MAX)
                dp[i] = (dp[i] < dp[i - x * x] + 1) ? dp[i] : dp[i - x * x] + 1;
    }
    return dp[n];
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("Minimum number of squares: %d\n", minSquares(n));
    return 0;
}