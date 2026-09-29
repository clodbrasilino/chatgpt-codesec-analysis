#include <stdio.h>
#include <limits.h>

int maxProfit(int k, const int* prices, int n) {
    if (n == 0 || k == 0) return 0;

    if (2 * k > n) {
        int profit = 0;
        for (int i = 1; i < n; i++) {
            if (prices[i] > prices[i - 1]) {
                profit += prices[i] - prices[i - 1];
            }
        }
        return profit;
    }

    int dp[k+1][n+1];
    for (int i = 0; i <= k; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0) dp[i][j] = 0;
        }
    }

    for (int i = 1; i <= k; i++) {
        int maxDiff = INT_MIN;
        for (int j = 1; j <= n; j++) {
            maxDiff = (maxDiff > dp[i-1][j-1] - prices[j-1]) ? maxDiff : dp[i-1][j-1] - prices[j-1];
            dp[i][j] = (dp[i][j-1] > prices[j-1] + maxDiff) ? dp[i][j-1] : prices[j-1] + maxDiff;
        }
    }
    return dp[k][n];
}

int main() {
    int prices[] = {7, 1, 5, 3, 6, 4};
    int n = sizeof(prices) / sizeof(prices[0]);
    int k = 2;
    printf("Maximum profit: %d\n", maxProfit(k, prices, n));
    return 0;
}