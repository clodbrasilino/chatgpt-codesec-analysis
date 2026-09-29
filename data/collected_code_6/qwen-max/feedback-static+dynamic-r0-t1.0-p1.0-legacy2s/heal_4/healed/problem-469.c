#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int maxProfit(int k, const int* prices, int n) {
    if (n == 0 || k == 0) return 0;

    if (k >= n / 2) {
        int profit = 0;
        for (int i = 1; i < n; i++) {
            if (prices[i] > prices[i - 1]) {
                profit += prices[i] - prices[i - 1];
            }
        }
        return profit;
    }

    int *buy = (int *)malloc((k + 1) * sizeof(int));
    int *sell = (int *)malloc((k + 1) * sizeof(int));

    for (int i = 1; i <= k; i++) {
        buy[i] = INT_MIN;
        sell[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 1; j <= k; j++) {
            if (i == 0) {
                buy[j] = -prices[0];
            } else {
                buy[j] = (buy[j] > sell[j - 1] - prices[i]) ? buy[j] : sell[j - 1] - prices[i];
                sell[j] = (sell[j] > buy[j] + prices[i]) ? sell[j] : buy[j] + prices[i];
            }
        }
    }

    int max_profit = 0;
    for (int i = 1; i <= k; i++) {
        max_profit = (max_profit > sell[i]) ? max_profit : sell[i];
    }

    free(buy);
    free(sell);
    return max_profit;
}

int main() {
    int prices[] = {3, 3, 5, 0, 0, 3, 1, 4};
    int n = sizeof(prices) / sizeof(prices[0]);
    int k = 2;
    int max_profit = maxProfit(k, prices, n);
    printf("Maximum Profit: %d\n", max_profit);
    return 0;
}