#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 7, got 0
  *  test case 2 failed: expected 2, got 0
  *  test case 0 failed: expected 10, got 5
  */

int max_profit(int k, const int *prices, int n) {
    if (n <= 1 || k <= 0) {
        return 0;
    }

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

    if (buy == NULL || sell == NULL) {
        free(buy);
        free(sell);
        return 0;
    }

    for (int i = 0; i <= k; i++) {
        buy[i] = INT_MIN;
        sell[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        int prev_sell = 0;
        for (int j = 1; j <= k; j++) {
            int old_buy = buy[j];
            int old_sell = sell[j];
            
            buy[j] = (old_buy > prev_sell - prices[i]) ? old_buy : (prev_sell - prices[i]);
            sell[j] = (old_sell > old_buy + prices[i]) ? old_sell : (old_buy + prices[i]);
            
            prev_sell = old_sell;
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

    int profit = max_profit(k, prices, n);
    printf("Maximum profit: %d\n", profit);

    int prices2[] = {1, 2, 3, 4, 5};
    int n2 = sizeof(prices2) / sizeof(prices2[0]);
    int k2 = 2;

    int profit2 = max_profit(k2, prices2, n2);
    printf("Maximum profit: %d\n", profit2);

    int prices3[] = {7, 6, 4, 3, 1};
    int n3 = sizeof(prices3) / sizeof(prices3[0]);
    int k3 = 2;

    int profit3 = max_profit(k3, prices3, n3);
    printf("Maximum profit: %d\n", profit3);

    return 0;
}