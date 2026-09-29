#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

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
    int* sell = (int*)malloc(k * sizeof(int));

    if (buy == NULL || sell == NULL) {
        free(buy);
        free(sell);
        return 0;
    }

    for (int i = 0; i < k; i++) {
        buy[i] = INT_MIN;
        sell[i] = 0;
    }

    for (int i = 0; i < pricesSize; i++) {
        int prev_sell = 0;
        for (int j = 0; j < k; j++) {
            if (prev_sell - prices[i] > buy[j]) {
                buy[j] = prev_sell - prices[i];
            }
            if (buy[j] + prices[i] > sell[j]) {
                sell[j] = buy[j] + prices[i];
            }
            prev_sell = sell[j];
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
    int size1 = sizeof(prices1) / sizeof(prices1[0]);
    int profit1 = maxProfit(k1, prices1, size1);
    printf("%d\n", profit1);

    int prices2[] = {3, 2, 6, 5, 0, 3};
    int k2 = 2;
    int size2 = sizeof(prices2) / sizeof(prices2[0]);
    int profit2 = maxProfit(k2, prices2, size2);
    printf("%d\n", profit2);

    int prices3[] = {1, 2, 3, 4, 5};
    int k3 = 2;
    int size3 = sizeof(prices3) / sizeof(prices3[0]);
    int profit3 = maxProfit(k3, prices3, size3);
    printf("%d\n", profit3);

    return 0;
}