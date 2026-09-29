#include <stdio.h>
#include <stdlib.h>

int maxProfit(int k, const int* prices, int pricesSize) {
    if (k <= 0 || pricesSize <= 1) {
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
    int* sell = (int*)calloc(k, sizeof(int));

    if (buy == NULL || sell == NULL) {
        free(buy);
        free(sell);
        return 0;
    }

    for (int i = 0; i < k; i++) {
        buy[i] = -prices[0];
    }

    for (int i = 1; i < pricesSize; i++) {
        for (int j = 0; j < k; j++) {
            int prev_sell = (j == 0) ? 0 : sell[j - 1];
            if (prev_sell - prices[i] > buy[j]) {
                buy[j] = prev_sell - prices[i];
            }
            if (buy[j] + prices[i] > sell[j]) {
                sell[j] = buy[j] + prices[i];
            }
        }
    }

    int result = sell[k - 1];
    free(buy);
    free(sell);
    return result;
}

int main() {
    int prices1[] = {3, 2, 6, 5, 0, 3};
    int k1 = 2;
    int size1 = sizeof(prices1) / sizeof(prices1[0]);
    printf("%d\n", maxProfit(k1, prices1, size1));

    int prices2[] = {1, 2, 3, 4, 5};
    int k2 = 2;
    int size2 = sizeof(prices2) / sizeof(prices2[0]);
    printf("%d\n", maxProfit(k2, prices2, size2));

    int prices3[] = {7, 6, 4, 3, 1};
    int k3 = 2;
    int size3 = sizeof(prices3) / sizeof(prices3[0]);
    printf("%d\n", maxProfit(k3, prices3, size3));

    return 0;
}