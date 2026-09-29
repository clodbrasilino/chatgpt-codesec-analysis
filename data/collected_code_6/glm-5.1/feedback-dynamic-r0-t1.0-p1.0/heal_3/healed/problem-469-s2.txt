#include <stdio.h>
#include <stdlib.h>

int max_profit(int k, int *prices, int prices_size) {
    if (prices_size <= 1 || k <= 0) {
        return 0;
    }

    if (k >= prices_size / 2) {
        int profit = 0;
        for (int i = 1; i < prices_size; i++) {
            if (prices[i] > prices[i - 1]) {
                profit += prices[i] - prices[i - 1];
            }
        }
        return profit;
    }

    int *buy = (int *)malloc(k * sizeof(int));
    int *sell = (int *)malloc(k * sizeof(int));
    
    if (buy == NULL || sell == NULL) {
        free(buy);
        free(sell);
        return 0;
    }

    for (int i = 0; i < k; i++) {
        buy[i] = -prices[0];
        sell[i] = 0;
    }

    for (int i = 1; i < prices_size; i++) {
        for (int j = 0; j < k; j++) {
            if (j == 0) {
                buy[j] = (buy[j] > -prices[i]) ? buy[j] : -prices[i];
            } else {
                buy[j] = (buy[j] > sell[j - 1] - prices[i]) ? buy[j] : sell[j - 1] - prices[i];
            }
            sell[j] = (sell[j] > buy[j] + prices[i]) ? sell[j] : buy[j] + prices[i];
        }
    }

    int result = sell[k - 1];
    free(buy);
    free(sell);
    
    return result;
}

int main() {
    int prices1[] = {2, 4, 1};
    int k1 = 2;
    printf("%d\n", max_profit(k1, prices1, sizeof(prices1) / sizeof(prices1[0])));

    int prices2[] = {3, 2, 6, 5, 0, 3};
    int k2 = 2;
    printf("%d\n", max_profit(k2, prices2, sizeof(prices2) / sizeof(prices2[0])));

    int prices0[] = {10, 5, 7};
    int k0 = 1;
    printf("%d\n", max_profit(k0, prices0, sizeof(prices0) / sizeof(prices0[0])));

    return 0;
}