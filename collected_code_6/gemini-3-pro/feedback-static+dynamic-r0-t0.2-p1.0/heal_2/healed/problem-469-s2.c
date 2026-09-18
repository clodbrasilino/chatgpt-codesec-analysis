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

    int** dp = (int**)malloc((k + 1) * sizeof(int*));
    for (int i = 0; i <= k; i++) {
        dp[i] = (int*)calloc(pricesSize, sizeof(int));
    }

    for (int i = 1; i <= k; i++) {
        int local_max = -prices[0];
        for (int j = 1; j < pricesSize; j++) {
            int no_transaction = dp[i][j - 1];
            int transaction = prices[j] + local_max;
            dp[i][j] = no_transaction > transaction ? no_transaction : transaction;

            int current_local_max = dp[i - 1][j] - prices[j];
            local_max = local_max > current_local_max ? local_max : current_local_max;
        }
    }

    int result = dp[k][pricesSize - 1];

    for (int i = 0; i <= k; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}

int main(void) {
    int prices[] = {3, 2, 6, 5, 0, 3};
    int k = 2;
    int size = sizeof(prices) / sizeof(prices[0]);
    
    int profit = maxProfit(k, prices, size);
    printf("%d\n", profit);
    
    return 0;
}