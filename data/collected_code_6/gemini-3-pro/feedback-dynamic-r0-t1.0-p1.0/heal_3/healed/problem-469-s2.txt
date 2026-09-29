#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int maxProfit(int k, int* prices, int pricesSize) {
    if (pricesSize <= 1 || k <= 0 || prices == NULL) {
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
        return 0;
    }

    for (int i = 1; i <= k; i++) {
        int max_diff = -prices[0];
        for (int j = 1; j < pricesSize; j++) {
            int temp = dp[j];
            dp[j] = max(dp[j - 1], prices[j] + max_diff