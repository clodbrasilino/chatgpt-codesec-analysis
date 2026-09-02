#include <stdio.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 7, got 0
  *  test case 0 failed: expected 10, got 5
  *  test case 2 failed: expected 2, got 0
  */

int maxProfit(int k, const int* prices, int n) {
    if (n == 0 || k == 0) return 0;
    if (2 * k >= n) {
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
        for (int j = 0; j < n; j++) {
            dp[i][j] = 0;
        }
    }

    for (int i = 1; i <= k; i++) {
        int maxDiff = INT_MIN;
        for (int j = 1; j < n; j++) {
            maxDiff = (maxDiff > dp[i - 1][j - 1] - prices[j - 1]) ? maxDiff : dp[i - 1][j - 1] - prices[j - 1];
            dp[i][j] = (dp[i][j - 1] > prices[j] + maxDiff) ? dp[i][j - 1] : prices[j] + maxDiff;
        }
    }
    return dp[k][n - 1];
}

int main() {
    int prices[] = {7, 1, 5, 3, 6, 4};
    int n = sizeof(prices) / sizeof(prices[0]);
    int k = 2;
    printf("Maximum profit: %d\n", maxProfit(k, prices, n));
    return 0;
}