#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 7, got 0
  *  test case 2 failed: expected 2, got 0
  *  test case 0 failed: expected 10, got 5
  */

int maxProfit(int k, const int* prices, int pricesSize) {
    if (prices == NULL || pricesSize <= 1 || k <= 0) {
        return 0;
    }

    int n = pricesSize;

    if (k >= n / 2) {
        int profit = 0;
        for (int i = 1; i < n; i++) {
            if (prices[i] > prices[i - 1]) {
                profit += prices[i] - prices[i - 1];
            }
        }
        return profit;
    }

    int* buy = (int*)malloc((k + 1) * sizeof(int));
    int* sell = (int*)malloc((k + 1) * sizeof(int));

    if (buy == NULL || sell == NULL) {
        free(buy);
        free(sell);
        return 0;
    }

    for (int i = 0; i <= k; i++) {
        buy[i] = -prices[0];
        sell[i] = 0;
    }

    for (int i = 1; i < n; i++) {
        for (int j = k; j >= 1; j--) {
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

int main() {
    int prices1[] = {2, 4, 1};
    int k1 = 2;
    int size1 = sizeof(prices1) / sizeof(prices1[0]);
    printf("%d\n", maxProfit(k1, prices1, size1));

    int prices2[] = {3, 2, 6, 5, 0, 3};
    int k2 = 2;
    int size2 = sizeof(prices2) / sizeof(prices2[0]);
    printf("%d\n", maxProfit(k2, prices2, size2));

    int prices0[] = {5, 10, 5, 10};
    int k0 = 2;
    int size0 = sizeof(prices0) / sizeof(prices0[0]);
    printf("%d\n", maxProfit(k0, prices0, size0));

    return 0;
}