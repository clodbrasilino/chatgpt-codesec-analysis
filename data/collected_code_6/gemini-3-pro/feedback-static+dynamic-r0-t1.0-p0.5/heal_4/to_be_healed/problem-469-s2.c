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

    if (!buy || !sell) {
        if (buy) free(buy);
        if (sell) free(sell);
        return 0;
    }

    for (int i = 0; i <= k; i++) {
        buy[i] = -1000000000;
        sell[i] = 0;
    }

    for (int i = 0; i < pricesSize; i++) {
        for (int j = 1; j <= k; j++) {
            int current_buy = sell[j - 1] - prices[i];
            if (buy[j] < current_buy) {
                buy[j] = current_buy;
            }
            int current_sell = buy[j] + prices[i];
            if (sell[j] < current_sell) {
                sell[j] = current_sell;
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

    printf("%d\n", maxProfit(k, prices, pricesSize));

    return 0;
}