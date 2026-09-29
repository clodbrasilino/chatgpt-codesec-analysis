#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 7, got 0
  *  test case 2 failed: expected 2, got 0
  *  test case 0 failed: expected 10, got 5
  */

int maxProfit(int k, int* prices, int pricesSize) {
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

    int *profit_buy = (int *)malloc((k + 1) * sizeof(int));
    int *profit_sell = (int *)malloc((k + 1) * sizeof(int));

    for (int i = 1; i <= k; ++i) {
        profit_buy[i] = INT_MIN;
        profit_sell[i] = 0;
    }

    for (int i = 0; i < pricesSize; ++i) {
        for (int j = 1; j <= k; ++j) {
            if (i != 0) {
                profit_buy[j] = (profit_buy[j] > profit_sell[j - 1] - prices[i]) ? profit_buy[j] : profit_sell[j - 1] - prices[i];
            } else {
                profit_buy[j] = -prices[i];
            }
            profit_sell[j] = (profit_sell[j] > profit_buy[j] + prices[i]) ? profit_sell[j] : profit_buy[j] + prices[i];
        }
    }

    int result = 0;
    for (int j = 1; j <= k; ++j) {
        result = (result > profit_sell[j]) ? result : profit_sell[j];
    }

    free(profit_buy);
    free(profit_sell);

    return result;
}

int main() {
    int k = 2;
    int prices[] = {2, 4, 1};
    int pricesSize = sizeof(prices) / sizeof(prices[0]);

    printf("%d\n", maxProfit(k, prices, pricesSize));

    return 0;
}