#include <stdio.h>

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

    int dp[k + 1][n];
    for (int i = 0; i <= k; i++) {
        dp[i][0] = 0;
    }
    for (int j = 0; j < n; j++) {
        dp[0][j] = 0;
    }

    for (int i = 1; i <= k; i++) {
        int maxDiff = -prices[0];
        for (int j = 1; j < n; j++) {
            dp[i][j] = (dp[i][j - 1] > prices[j] + maxDiff) ? dp[i][j - 1] : prices[j] + maxDiff;
            maxDiff = (maxDiff > dp[i - 1][j] - prices[j]) ? maxDiff : dp[i - 1][j] - prices[j];
        }
    }
    return dp[k][n - 1];
}

int main() {
    int prices[] = {1, 5, 3, 8};
    int n = sizeof(prices) / sizeof(prices[0]);
    int k = 2;
    printf("Maximum profit: %d\n", maxProfit(k, prices, n));
    
    int prices2[] = {3, 2, 6, 5, 0, 3};
    n = sizeof(prices2) / sizeof(prices2[0]);
    k = 2;
    printf("Maximum profit: %d\n", maxProfit(k, prices2, n));

    int prices3[] = {7, 6, 4, 3, 1};
    n = sizeof(prices3) / sizeof(prices3[0]);
    k = 1;
    printf("Maximum profit: %d\n", maxProfit(k, prices3, n));

    return 0;
}