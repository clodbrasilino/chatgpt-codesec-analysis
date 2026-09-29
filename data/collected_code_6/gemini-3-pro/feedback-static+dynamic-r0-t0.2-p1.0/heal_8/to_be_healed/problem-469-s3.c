#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
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
        buy[i] = -prices[0];
        sell[i] = 0;
    }

    for (int i = 1; i < pricesSize; i++) {
        for (int j = k; j >= 1; j--) {
            sell[j] = MAX(sell[j], buy[j] + prices[i]);
            buy[j] = MAX(buy[j], sell[j - 1] - prices[i]);
        }
    }

    int result = sell[k];
    
    free(buy);
    free(sell);
    
    return result;
}

int main(void) {
    int prices[] = {3, 2, 6, 5, 0, 3};
    int pricesSize = sizeof(prices) / sizeof(prices[0]);
    int k = 2;
    
    int profit = maxProfit(k, prices, pricesSize);
    printf("Max Profit: %d\n", profit);
    
    return 0;
}