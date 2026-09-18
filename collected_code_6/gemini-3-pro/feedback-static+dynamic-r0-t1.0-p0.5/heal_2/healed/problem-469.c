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

    int* dp = (int*)calloc(pricesSize, sizeof(int));
    if (dp == NULL) {
        return -1;
    }

    for (int i = 1; i <= k; i++) {
        int max_diff = -prices[0];
        for (int j = 1; j < pricesSize; j++) {
            int prev_dp = dp[j];
            
            int curr_profit = prices[j] + max_diff;
            if (dp[j - 1] > curr_profit) {
                dp[j] = dp[j - 1];
            } else {
                dp[j] = curr_profit;
            }

            int diff = prev_dp - prices[j];
            if (diff > max_diff) {
                max_diff = diff;
            }
        }
    }

    int result = dp[pricesSize - 1];
    free(dp);

    return result;
}

int main(void) {
    int prices[] = {3, 2, 6, 5, 0, 3};
    int k = 2;
    int pricesSize = sizeof(prices) / sizeof(prices[0]);

    int profit = maxProfit(k, prices, pricesSize);
    
    printf("Max Profit: %d\n", profit);
    
    return 0;
}