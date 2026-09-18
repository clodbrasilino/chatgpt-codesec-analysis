#include <stdio.h>
#include <stdlib.h>

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
        buy[i] = -1000000000;
        sell[i] = 0;
    }

    for (int j = 0; j < pricesSize; j++) {
        for (int i = 1; i <= k; i++) {
            int current_buy = sell[i - 1] - prices[j];
            if (current_buy > buy[i]) {
                buy[i] = current_buy;
            }
            int current_sell = buy[i] + prices[j];
            if (current_sell > sell[i]) {
                sell[i] = current_sell;
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
    if (scanf("%d", &k) != 1) return 0;

    int capacity = 10000;
    int* prices = (int*)malloc(capacity * sizeof(int));
    if (!prices) return 0;
    int size = 0;

    while (scanf("%d", &prices[size]) == 1) {
        size++;
        if (size >= capacity) {
            capacity *= 2;
            int* temp = (int*)realloc(prices, capacity * sizeof(int));
            if (!temp) {
                free(prices);
                return 0;
            }
            prices = temp;
        }
    }

    if (size > 0) {
        printf("%d\n", maxProfit(k, prices, size));
    }

    free(prices);
    return 0;
}