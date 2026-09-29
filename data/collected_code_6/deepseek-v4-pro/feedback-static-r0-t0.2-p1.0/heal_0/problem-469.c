#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int max_profit(int k, int *prices, int n) {
    if (n <= 1 || k <= 0) {
        return 0;
    }

    if (k >= n / 2) {
        int profit = 0;
        for (int i = 1; i < n; i++) {
            if (prices[i] > prices[i - 1]) {
                profit += prices[i] - prices[i - 1];
            }
        }
        return profit;
    }

    int *buy = (int *)malloc((k + 1) * sizeof(int));
    int *sell = (int *)malloc((k + 1) * sizeof(int));

    if (buy == NULL || sell == NULL) {
        free(buy);
        free(sell);
        return 0;
    }

    for (int i = 0; i <= k; i++) {
        buy[i] = INT_MIN;
        sell[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 1; j <= k; j++) {
            buy[j] = (buy[j] > sell[j - 1] - prices[i]) ? buy[j] : (sell[j - 1] - prices[i]);
            sell[j] = (sell[j] > buy[j] + prices[i]) ? sell[j] : (buy[j] + prices[i]);
        }
    }

    int result = sell[k];
    free(buy);
    free(sell);
    return result;
}

int main(void) {
    int prices[] = {3, 2, 6, 5, 0, 3};
    int n = sizeof(prices) / sizeof(prices[0]);
    int k = 2;

    int profit = max_profit(k, prices, n);
    printf("Maximum profit: %d\n", profit);

    int prices2[] = {1, 2, 3, 4, 5};
    int n2 = sizeof(prices2) / sizeof(prices2[0]);
    int k2 = 2;

    int profit2 = max_profit(k2, prices2, n2);
    printf("Maximum profit: %d\n", profit2);

    int prices3[] = {7, 6, 4, 3, 1};
    int n3 = sizeof(prices3) / sizeof(prices3[0]);
    int k3 = 2;

    int profit3 = max_profit(k3, prices3, n3);
    printf("Maximum profit: %d\n", profit3);

    return 0;
}