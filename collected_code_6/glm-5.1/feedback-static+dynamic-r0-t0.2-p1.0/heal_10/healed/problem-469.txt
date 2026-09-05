#include <stdio.h>
#include <stdlib.h>

int maxProfit(int k, const int* prices, int pricesSize) {
    if (k <= 0 || pricesSize <= 1) {
        return 0;
    }

    if (k >= pricesSize / 2) {
        int profit = 0;
        for (int i = 1; i < pricesSize; i++) {
            if (prices[i] > prices[i - 1]) {
                profit += prices[i] - prices[i - 1];
            }
        }
        return profit;
    }

    int* dp = (int*)malloc(pricesSize * sizeof(int));
    for (int i = 0; i < pricesSize; i++) {
        dp[i] = 0;
    }

    for (int j = 1; j <= k; j++) {
        int max_diff = -prices[0];
        int prev = 0;
        for (int i = 1; i < pricesSize; i++) {
            int temp = dp[i];
            int sell = prices[i] + max_diff;
            dp[i] = sell > dp[i - 1] ? sell : dp[i - 1];
            int buy = -prices[i] + prev;
            if (buy > max_diff) {
                max_diff = buy;
            }
            prev = temp;
        }
    }

    int result = dp[pricesSize - 1];
    free(dp);
    return result;
}

int main() {
    int prices1[] = {3, 2, 6, 5, 0, 3};
    int k1 = 2;
    int size1 = sizeof(prices1) / sizeof(prices1[0]);
    printf("%d\n", maxProfit(k1, prices1, size1));

    int prices2[] = {1, 2, 3, 4, 5};
    int k2 = 2;
    int size2 = sizeof(prices2) / sizeof(prices2[0]);
    printf("%d\n", maxProfit(k2, prices2, size2));

    int prices3[] = {7, 6, 4, 3, 1};
    int k3 = 2;
    int size3 = sizeof(prices3) / sizeof(prices3[0]);
    printf("%d\n", maxProfit(k3, prices3, size3));

    return 0;
}