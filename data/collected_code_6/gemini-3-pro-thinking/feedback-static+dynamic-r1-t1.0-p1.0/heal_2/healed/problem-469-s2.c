#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int maxProfit(int k, const int* prices, int n) {
    if (prices == NULL || n <= 1 || k <= 0) {
        return 0;
    }

    if (k >= n / 2) {
        int max_profit = 0;
        for (int i = 1; i < n; i++) {
            if (prices[i] > prices[i - 1]) {
                max_profit += prices[i] - prices[i - 1];
            }
        }
        return max_profit;
    }

    int *buy = (int *)malloc(((size_t)k + 1) * sizeof(int));
    if (buy == NULL) {
        return 0;
    }

    int *sell = (int *)malloc(((size_t)k + 1) * sizeof(int));
    if (sell == NULL) {
        free(buy);
        return 0;
    }

    for (int j = 0; j <= k; j++) {
        buy[j] = INT_MIN;
        sell[j] = 0;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 1; j <= k; j++) {
            if (sell[j - 1] - prices[i] > buy[j]) {
                buy[j] = sell[j - 1] - prices[i];
            }
            if (buy[j] + prices[i] > sell[j]) {
                sell[j] = buy[j] + prices[i];
            }
        }
    }

    int result = sell[k];
    
    free(buy);
    free(sell);
    
    return result;
}

int main(void) {
    int prices[] = {3, 2, 6, 5, 0, 3};
    int n = sizeof(prices) / sizeof(prices[0]);
    int k = 2;
    
    int max_profit = maxProfit(k, prices, n);
    printf("Max Profit: %d\n", max_profit);
    
    return 0;
}