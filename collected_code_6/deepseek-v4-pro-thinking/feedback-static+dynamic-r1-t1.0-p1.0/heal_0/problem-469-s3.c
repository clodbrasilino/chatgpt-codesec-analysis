#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int maxProfit(int k, int prices[], int n) {
    if (n < 0 || (prices == NULL && n > 0)) {
        return -1;
    }

    if (k <= 0 || n < 2) {
        return 0;
    }

    if (k >= n / 2) {
        long long total = 0;
        for (int i = 1; i < n; ++i) {
            if (prices[i] > prices[i - 1]) {
                total += (long long)prices[i] - prices[i - 1];
                if (total > INT_MAX) {
                    return -1;
                }
            }
        }
        return (int)total;
    }

    size_t slots = (size_t)k + 1;
    long long *buy = malloc(slots * sizeof(*buy));
    long long *sell = malloc(slots * sizeof(*sell));
    if (buy == NULL || sell == NULL) {
        free(buy);
        free(sell);
        return -1;
    }

    for (int j = 0; j <= k; ++j) {
        buy[j] = LLONG_MIN;
        sell[j] = 0;
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 1; j <= k; ++j) {
            long long candidate_buy = sell[j - 1] - prices[i];
            if (candidate_buy > buy[j]) {
                buy[j] = candidate_buy;
            }

            long long candidate_sell = buy[j] + prices[i];
            if (candidate_sell > sell[j]) {
                sell[j] = candidate_sell;
            }
        }
    }

    long long result = sell[k];
    free(buy);
    free(sell);

    if (result < 0 || result > INT_MAX) {
        return -1;
    }
    return (int)result;
}

int main(void) {
    int prices[] = {3, 2, 6, 5, 0, 3};
    int k = 2;
    int n = sizeof(prices) / sizeof(prices[0]);
    int result = maxProfit(k, prices, n);
    if (result >= 0) {
        printf("Maximum profit: %d\n", result);
    } else {
        printf("Error computing maximum profit\n");
    }
    return 0;
}