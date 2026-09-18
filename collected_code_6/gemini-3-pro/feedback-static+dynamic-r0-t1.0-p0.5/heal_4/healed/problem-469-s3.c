#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

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

    int* buy = (int*)malloc(sizeof(int) * (k + 1));
    int* sell = (int*)malloc(sizeof(int) * (k + 1));

    for (int i = 0; i <= k; i++) {
        buy[i] = INT_MIN;
        sell[i] = 0;
    }

    for (int i = 0; i < pricesSize; i++) {
        for (int j = 1; j <= k; j++) {
            buy[j] = MAX(buy[j], sell[j - 1] - prices[i]);
            sell[j] = MAX(sell[j], buy[j] + prices[i]);
        }
    }

    int result = sell[k];
    
    free(buy);
    free(sell);

    return result;
}

int main(void) {
    int k, pricesSize;
    if (scanf("%d %d", &k, &pricesSize) == 2) {
        int* prices = (int*)malloc(pricesSize * sizeof(int));
        for (int i = 0; i < pricesSize; i++) {
            scanf("%d", &prices[i]);
        }
        printf("%d\n", maxProfit(k, prices, pricesSize));
        free(prices);
    }
    return 0;
}