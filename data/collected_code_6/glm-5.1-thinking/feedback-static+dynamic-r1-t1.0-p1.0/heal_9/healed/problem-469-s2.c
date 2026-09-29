#include <stdio.h>
#include <stdlib.h>

int maxProfit(int k, const int* prices, int pricesSize) {
    if (prices == NULL || pricesSize <= 1 || k <= 0) {
        return 0;
    }

    int n = pricesSize;

    if (k >= n / 2) {
        long long profit = 0;
        for (int i = 1; i < n; i++) {
            if (prices[i] > prices[i - 1]) {
                profit += prices[i] - prices[i - 1];
            }
        }
        return (int)profit;
    }

    long long *buy = (long long *)malloc((k + 1) * sizeof(long long));
    long long *sell = (long long *)malloc((k + 1) * sizeof(long long));

    if (buy == NULL || sell == NULL) {
        free(buy);
        free(sell);
        return 0;
    }

    sell[0] = 0;
    for (int i = 1; i <= k; i++) {
        buy[i] = -prices[0];
        sell[i] = 0;
    }

    for (int i = 1; i < n; i++) {
        for (int j = 1; j <= k; j++) {
            buy[j] = buy[j] > sell[j - 1] - prices[i] ? buy[j] : sell[j - 1] - prices[i];
            sell[j] = sell[j] > buy[j] + prices[i] ? sell[j] : buy[j] + prices[i];
        }
    }

    long long result = sell[k];
    free(buy);
    free(sell);
    return (int)result;
}

int main() {
    int prices1[] = {2, 4, 1};
    int k1 = 2;
    int size1 = sizeof(prices1) / sizeof(prices1[0]);
    printf("%d\n", maxProfit(k1, prices1, size1));

    int prices2[] = {3, 2, 6, 5, 0, 3};
    int k2 = 2;
    int size2 = sizeof(prices2) / sizeof(prices2[0]);
    printf("%d\n", maxProfit(k2, prices2, size2));

    int prices0[] = {5, 10, 5, 10};
    int k0 = 2;
    int size0 = sizeof(prices0) / sizeof(prices0[0]);
    printf("%d\n", maxProfit(k0, prices0, size0));

    return 0;
}