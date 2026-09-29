#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
 /* Possible weaknesses found:
  *  test case 0 failed: expected 10, got <no output>
  *  test case 2 failed: expected 2, got <no output>
  *  test case 1 failed: expected 7, got <no output>
  */

int maxProfit(int k, const int* prices, int pricesSize) {
    if (pricesSize <= 1 || k <= 0 || prices == NULL) {
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

    int* buy = (int*)malloc(k * sizeof(int));
    int* sell = (int*)malloc(k * sizeof(int));
    
    for (int i = 0; i < k; i++) {
        buy[i] = -prices[0];
        sell[i] = 0;
    }

    for (int i = 1; i < pricesSize; i++) {
        buy[0] = MAX(buy[0], -prices[i]);
        sell[0] = MAX(sell[0], buy[0] + prices[i]);
        for (int j = 1; j < k; j++) {
            buy[j] = MAX(buy[j], sell[j - 1] - prices[i]);
            sell[j] = MAX(sell[j], buy[j] + prices[i]);
        }
    }

    int result = sell[k - 1];
    free(buy);
    free(sell);
    
    return result;
}

int main(void) {
    int prices[] = {3, 2, 6, 5, 0, 3};
    int k = 2;
    int pricesSize = sizeof(prices) / sizeof(prices[0]);
    
    int result = maxProfit(k, prices, pricesSize);
    printf("Maximum Profit: %d\n", result);
    
    return 0;
}