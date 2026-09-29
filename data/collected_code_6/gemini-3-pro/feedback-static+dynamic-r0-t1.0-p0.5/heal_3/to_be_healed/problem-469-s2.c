#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 10, got <no output>
  *  test case 2 failed: expected 2, got <no output>
  *  test case 1 failed: expected 7, got <no output>
  */

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

    int* buy = (int*)malloc((k + 1) * sizeof(int));
    int* sell = (int*)malloc((k + 1) * sizeof(int));

    if (buy == NULL || sell == NULL) {
        if (buy) free(buy);
        if (sell) free(sell);
        return -1;
    }

    for (int i = 0; i <= k; i++) {
        buy[i] = -1000000000;
        sell[i] = 0;
    }

    for (int i = 0; i < pricesSize; i++) {
        for (int j = 1; j <= k; j++) {
            if (buy[j] < sell[j - 1] - prices[i]) {
                buy[j] = sell[j - 1] - prices[i];
            }
            if (sell[j] < buy[j] + prices[i]) {
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
    int k = 2;
    int pricesSize = sizeof(prices) / sizeof(prices[0]);

    int profit = maxProfit(k, prices, pricesSize);
    if (profit != -1) {
        printf("%d\n", profit);
    }

    return 0;
}