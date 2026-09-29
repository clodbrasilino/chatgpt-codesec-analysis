#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 7, got 0
  *  test case 0 failed: expected 10, got 5
  *  test case 2 failed: expected 2, got 0
  */

int maxProfit(int k, const int* prices, int pricesSize) {
    if (pricesSize == 0 || k == 0) return 0;
    if (2 * k > pricesSize) {
        int profit = 0;
        for (int i = 1; i < pricesSize; i++) {
            if (prices[i] > prices[i - 1]) {
                profit += prices[i] - prices[i - 1];
            }
        }
        return profit;
    }

    int *dp = (int *)malloc((k + 1) * sizeof(int));
    int *profit = (int *)malloc((k + 1) * sizeof(int));
    for (int i = 0; i <= k; i++) {
        dp[i] = INT_MAX;
        profit[i] = 0;
    }

    for (int i = 0; i < pricesSize; i++) {
        for (int j = 1; j <= k; j++) {
            dp[j] = (dp[j] < prices[i] - profit[j - 1]) ? dp[j] : prices[i] - profit[j - 1];
            profit[j] = (profit[j] > prices[i] - dp[j]) ? profit[j] : prices[i] - dp[j];
        }
    }

    int max_profit = 0;
    for (int i = 1; i <= k; i++) {
        if (profit[i] > max_profit) {
            max_profit = profit[i];
        }
    }

    free(dp);
    free(profit);
    return max_profit;
}

int main() {
    int prices[] = {3, 3, 5, 0, 0, 3, 1, 4};
    int pricesSize = sizeof(prices) / sizeof(prices[0]);
    int k = 2;
    int result = maxProfit(k, prices, pricesSize);
    printf("Maximum Profit: %d\n", result);
    return 0;
}