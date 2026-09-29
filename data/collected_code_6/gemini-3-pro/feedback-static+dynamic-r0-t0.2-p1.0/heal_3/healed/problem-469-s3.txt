#include <stdio.h>
#include <stdlib.h>

int maxProfit(int k, const int* prices, int pricesSize) {
    if (pricesSize <= 1 || k <= 0) {
        return 0;
    }

    if (k >= pricesSize / 2) {
        int max_profit = 0;
        for (int i = 1; i < pricesSize; i++) {
            if (prices[i] > prices[i - 1]) {
                max_profit += prices[i] - prices[i - 1];
            }
        }
        return max_profit;
    }

    int* dp = (int*)malloc(2 * k * sizeof(int));
    if (!dp) {
        return 0;
    }

    for (int i = 0; i < k; i++) {
        dp[2 * i] = -prices[0];
        dp[2 * i + 1] = 0;
    }

    for (int i = 1; i < pricesSize; i++) {
        dp[0] = (dp[0] > -prices[i]) ? dp[0] : -prices[i];
        dp[1] = (dp[1] > dp[0] + prices[i]) ? dp[1] : dp[0] + prices[i];
        for (int j = 1; j < k; j++) {
            dp[2 * j] = (dp[2 * j] > dp[2 * j - 1] - prices[i]) ? dp[2 * j] : dp[2 * j - 1] - prices[i];
            dp[2 * j + 1] = (dp[2 * j + 1] > dp[2 * j] + prices[i]) ? dp[2 * j + 1] : dp[2 * j] + prices[i];
        }
    }

    int result = dp[2 * k - 1];
    free(dp);
    return result;
}

int main() {
    int prices[] = {3, 2, 6, 5, 0, 3};
    int k = 2;
    int pricesSize = sizeof(prices) / sizeof(prices[0]);
    
    int result = maxProfit(k, prices, pricesSize);
    printf("%d\n", result);
    
    return 0;
}