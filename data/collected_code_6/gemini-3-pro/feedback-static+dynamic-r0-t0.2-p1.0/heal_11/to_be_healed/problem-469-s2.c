#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 10, got 5
  *  test case 2 failed: expected 2, got 0
  *  test case 1 failed: expected 7, got 0
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

    for (int i = 0; i <= k; i++) {
        buy[i] = -1000000000;
        sell[i] = 0;
    }

    for (int i = 0; i < pricesSize; i++) {
        for (int j = k; j >= 1; j--) {
            if (buy[j] + prices[i] > sell[j]) {
                sell[j] = buy[j] + prices[i];
            }
            if (sell[j - 1] - prices[i] > buy[j]) {
                buy[j] = sell[j - 1] - prices[i];
            }
        }
    }

    int max_profit = sell[k];
    free(buy);
    free(sell);

    return max_profit;
}

int main() {
    int prices[] = {3, 2, 6, 5, 0, 3};
    int pricesSize = sizeof(prices) / sizeof(prices[0]);
    int k = 2;
    
    int result = maxProfit(k, prices, pricesSize);
    printf("%d\n", result);
    
    return 0;
}