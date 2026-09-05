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

    if (buy == NULL || sell == NULL) {
        free(buy);
        free(sell);
        return 0;
    }

    for (int i = 0; i < k; i++) {
        buy[i] = -prices[0];
        sell[i] = 0;
    }

    for (int i = 1; i < pricesSize; i++) {
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
    const int prices1[] = {2, 4, 1};
    int k1 = 2;
    printf("%d\n", maxProfit(k1, prices1, 3));

    const int prices2[] = {3, 2, 6, 5, 0, 3};
    int k2 = 2;
    printf("%d\n", maxProfit(k2, prices2, 6));

    const int prices3[] = {1, 2, 3, 4, 5};
    int k3 = 2;
    printf("%d\n", maxProfit(k3, prices3, 5));

    return 0;
}