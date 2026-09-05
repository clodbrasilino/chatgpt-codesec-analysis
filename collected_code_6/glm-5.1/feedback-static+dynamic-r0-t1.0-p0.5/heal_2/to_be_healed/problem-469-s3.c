#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 2, got 0
  *  test case 0 failed: expected 10, got 5
  *  test case 1 failed: expected 7, got 0
  */

int maxProfit(int k, const int* prices, int pricesSize) {
    if (pricesSize <= 1 || k <= 0) {
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
        buy[i] = -prices[0];
        sell[i] = 0;
    }

    for (int i = 1; i < pricesSize; i++) {
        buy[0] = (buy[0] > -prices[i]) ? buy[0] : -prices[i];
        sell[0] = (sell[0] > buy[0] + prices[i]) ? sell[0] : buy[0] + prices[i];

        for (int j = 1; j < k; j++) {
            int prev_sell = sell[j - 1];
            buy[j] = (buy[j] > prev_sell - prices[i]) ? buy[j] : prev_sell - prices[i];
            int current_buy = buy[j];
            sell[j] = (sell[j] > current_buy + prices[i]) ? sell[j] : current_buy + prices[i];
        }
    }

    int result = sell[k - 1];
    free(buy);
    free(sell);

    return result;
}

int main() {
    /* Possible weaknesses found:
     *  Variable 'prices1' can be declared as const array [constVariable]
     */
    int prices1[] = {2, 4, 1};
    int k1 = 2;
    printf("%d\n", maxProfit(k1, prices1, 3));

    /* Possible weaknesses found:
     *  Variable 'prices2' can be declared as const array [constVariable]
     */
    int prices2[] = {3, 2, 6, 5, 0, 3};
    int k2 = 2;
    printf("%d\n", maxProfit(k2, prices2, 6));

    /* Possible weaknesses found:
     *  Variable 'prices3' can be declared as const array [constVariable]
     */
    int prices3[] = {1, 2, 3, 4, 5};
    int k3 = 1;
    printf("%d\n", maxProfit(k3, prices3, 5));

    return 0;
}