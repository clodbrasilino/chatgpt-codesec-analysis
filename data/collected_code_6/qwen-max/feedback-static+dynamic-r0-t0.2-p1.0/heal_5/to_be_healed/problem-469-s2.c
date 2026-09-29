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
        for (int i = 1; i < pricesSize; ++i) {
            if (prices[i] > prices[i - 1]) {
                profit += prices[i] - prices[i - 1];
            }
        }
        return profit;
    }

    int *buy = (int *)malloc((k + 1) * sizeof(int));
    int *sell = (int *)malloc((k + 1) * sizeof(int));

    for (int i = 1; i <= k; ++i) {
        buy[i] = -INT_MAX;
        sell[i] = 0;
    }

    for (int i = 0; i < pricesSize; ++i) {
        for (int j = 1; j <= k; ++j) {
            buy[j] = (buy[j] > sell[j - 1] - prices[i]) ? buy[j] : sell[j - 1] - prices[i];
            sell[j] = (sell[j] > buy[j] + prices[i]) ? sell[j] : buy[j] + prices[i];
        }
    }

    int max_profit = sell[k];

    free(buy);
    free(sell);

    return max_profit;
}

int main() {
    const int prices[] = {3, 3, 5, 0, 0, 3, 1, 4};
    int k = 2;
    int pricesSize = sizeof(prices) / sizeof(prices[0]);
    int profit = maxProfit(k, prices, pricesSize);
    printf("Maximum Profit: %d\n", profit);
    return 0;
}