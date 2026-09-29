#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 10, got 5
  *  test case 1 failed: expected 7, got 0
  *  test case 2 failed: expected 2, got 0
  */

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

    int* buy = (int*)malloc(k * sizeof(int));
    int* sell = (int*)malloc(k * sizeof(int));

    if (buy == NULL || sell == NULL) {
        free(buy);
        free(sell);
        return 0;
    }

    for (int i = 0; i < k; i++) {
        buy[i] = INT_MIN;
        sell[i] = 0;
    }

    for (int i = 0; i < pricesSize; i++) {
        for (int j = 0; j < k; j++) {
            /* Possible weaknesses found:
             *  Value stored to 'prevBuy' during its initialization is never read [deadcode.DeadStores]
             *  Variable 'prevBuy' is assigned a value that is never used. [unreadVariable]
             */
            int prevBuy = (j > 0) ? buy[j - 1] : -prices[i];
            int prevSell = (j > 0) ? sell[j - 1] : 0;
            if (prevSell - prices[i] > buy[j]) {
                buy[j] = prevSell - prices[i];
            }
            if (buy[j] + prices[i] > sell[j]) {
                sell[j] = buy[j] + prices[i];
            }
        }
    }

    int result = sell[k - 1];
    free(buy);
    free(sell);
    return result;
}

int main() {
    int prices1[] = {3, 2, 6, 5, 0, 3};
    int k1 = 2;
    int size1 = sizeof(prices1) / sizeof(prices1[0]);
    int result1 = maxProfit(k1, prices1, size1);
    printf("%d\n", result1);

    int prices2[] = {1, 2, 3, 4, 5};
    int k2 = 1;
    int size2 = sizeof(prices2) / sizeof(prices2[0]);
    int result2 = maxProfit(k2, prices2, size2);
    printf("%d\n", result2);

    int prices3[] = {7, 6, 4, 3, 1};
    int k3 = 2;
    int size3 = sizeof(prices3) / sizeof(prices3[0]);
    int result3 = maxProfit(k3, prices3, size3);
    printf("%d\n", result3);

    return 0;
}