#include <stdio.h>
#include <stdlib.h>

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
    if (!buy || !sell) {
        if (buy) free(buy);
        if (sell) free(sell);
        return -1;
    }

    for (int i = 0; i < k; i++) {
        buy[i] = -1000000000;
        sell[i] = 0;
    }

    for (int i = 0; i < pricesSize; i++) {
        for (int j = 0; j < k; j++) {
            int prev_sell = (j == 0) ? 0 : sell[j - 1];
            buy[j] = buy[j] > prev_sell - prices[i] ? buy[j] : prev_sell - prices[i];
            sell[j] = sell[j] > buy[j] + prices[i] ? sell[j] : buy[j] + prices[i];
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

    int profit = maxProfit(k, prices, pricesSize);
    if (profit != -1) {
        printf("%d\n", profit);
    } else {
        printf("Memory allocation failed\n");
    }

    return 0;
}