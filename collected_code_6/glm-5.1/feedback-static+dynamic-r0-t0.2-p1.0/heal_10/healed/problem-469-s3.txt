#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int max_profit(int k, const int* prices, int prices_size) {
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

    for (int i = 0; i < prices_size; i++) {
        for (int j = 0; j < k; j++) {
            int prev_buy = (j == 0) ? -prices[i] : sell[j - 1] - prices[i];
            if (prev_buy > buy[j]) {
                buy[j] = prev_buy;
            }
            int current_sell = buy[j] + prices[i];
            if (current_sell > sell[j]) {
                sell[j] = current_sell;
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
    printf("%d\n", max_profit(k1, prices1, size1));

    int prices2[] = {1, 2, 3, 4, 5};
    int k2 = 2;
    int size2 = sizeof(prices2) / sizeof(prices2[0]);
    printf("%d\n", max_profit(k2, prices2, size2));

    int prices3[] = {7, 6, 4, 3, 1};
    int k3 = 2;
    int size3 = sizeof(prices3) / sizeof(prices3[0]);
    printf("%d\n", max_profit(k3, prices3, size3));

    return 0;
}