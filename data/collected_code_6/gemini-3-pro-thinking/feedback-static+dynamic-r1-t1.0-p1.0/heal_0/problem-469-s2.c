#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int maxProfit(int k, const int* prices, int n) {
    if (prices == NULL || n <= 1 || k <= 0) {
        return 0;
    }

    if (k >= n / 2) {
        int max_profit = 0;
        for (int i = 1; i < n; i++) {
            if (prices[i] > prices[i - 1]) {
                max_profit += prices[i] - prices[i - 1];
            }
        }
        return max_profit;
    }

    int *buy = (int *)malloc(((size_t)k + 1) * sizeof(int));
    if (buy == NULL) {
        return -1;
    }

    int *sell = (int *)malloc(((size_t)k + 1) * sizeof(int));
    if (sell == NULL) {
        free(buy);
        return -1;
    }

    for (int i = 0; i <= k; i++) {
        buy[i] = INT_MIN;
        sell[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 1; j <= k; j++) {
            if (sell[j - 1] - prices[i] > buy[j]) {
                buy[j] = sell[j - 1] - prices[i];
            }
            if (buy[j] + prices[i] > sell[j]) {
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
    int prices[] = {3, 2, 6, 5, 0, 3};
    int k = 2;
    int n = (int)(sizeof(prices) / sizeof(prices[0]));

    int result = maxProfit(k, prices, n);
    
    if (result == -1) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("%d\n", result);

    return EXIT_SUCCESS;
}