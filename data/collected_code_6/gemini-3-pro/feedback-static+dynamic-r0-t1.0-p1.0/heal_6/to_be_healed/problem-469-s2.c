#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 7, got 0
  *  test case 2 failed: expected 2, got 0
  *  test case 0 failed: expected 10, got 5
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

    int* buy = (int*)malloc((k + 1) * sizeof(int));
    int* sell = (int*)calloc(k + 1, sizeof(int));

    if (buy == NULL || sell == NULL) {
        free(buy);
        free(sell);
        return 0;
    }

    for (int i = 0; i <= k; i++) {
        buy[i] = -1000000000;
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
    int k;
    if (scanf("%d", &k) != 1) {
        return 0;
    }

    int capacity = 100;
    int pricesSize = 0;
    int* prices = (int*)malloc(capacity * sizeof(int));
    if (prices == NULL) {
        return 1;
    }

    while (scanf("%d", &prices[pricesSize]) == 1) {
        pricesSize++;
        if (pricesSize >= capacity) {
            capacity *= 2;
            int* temp = (int*)realloc(prices, capacity * sizeof(int));
            if (temp == NULL) {
                free(prices);
                return 1;
            }
            prices = temp;
        }
    }

    int profit = maxProfit(k, prices, pricesSize);
    printf("%d\n", profit);

    free(prices);
    return 0;
}