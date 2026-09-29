#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int max_profit(int k, const int prices[], int n) {
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

    for (int j = 0; j <= k; j++) {
        buy[j] = INT_MIN;
        sell[j] = 0;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 1; j <= k; j++) {
            buy[j] = (buy[j] > sell[j - 1] - prices[i]) ? buy[j] : sell[j - 1] - prices[i];
            sell[j] = (sell[j] > buy[j] + prices[i]) ? sell[j] : buy[j] + prices[i];
        }
    }

    int result = sell[k];
    free(buy);
    free(sell);
    return result;
}

int main(void) {
    int prices1[] = {2, 4, 1};
    int k1 = 2;
    int n1 = sizeof(prices1) / sizeof(prices1[0]);
    printf("%d\n", max_profit(k1, prices1, n1));

    int prices2[] = {3, 2, 6, 5, 0, 3};
    int k2 = 2;
    int n2 = sizeof(prices2) / sizeof(prices2[0]);
    printf("%d\n", max_profit(k2, prices2, n2));

    int prices3[] = {1, 2, 3, 4, 5};
    int k3 = 3;
    int n3 = sizeof(prices3) / sizeof(prices3[0]);
    printf("%d\n", max_profit(k3, prices3, n3));

    int prices4[] = {5, 4, 3, 2, 1};
    int k4 = 2;
    int n4 = sizeof(prices4) / sizeof(prices4[0]);
    printf("%d\n", max_profit(k4, prices4, n4));

    return 0;
}