#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int maxProfit(int k, const int *prices, int n) {
    if (prices == NULL || n <= 1 || k <= 0) {
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

    int *buy = (int *)malloc((size_t)k * sizeof(int));
    int *sell = (int *)malloc((size_t)k * sizeof(int));
    
    if (buy == NULL || sell == NULL) {
        free(buy);
        free(sell);
        return 0;
    }

    for (int i = 0; i < k; i++) {
        buy[i] = INT_MIN;
        sell[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++) {
            if (j == 0) {
                int candidate = -prices[i];
                if (candidate > buy[j]) {
                    buy[j] = candidate;
                }
            } else {
                if (sell[j - 1] != INT_MIN) {
                    int candidate = sell[j - 1] - prices[i];
                    if (candidate > buy[j]) {
                        buy[j] = candidate;
                    }
                }
            }
            
            if (buy[j] != INT_MIN) {
                int candidate = buy[j] + prices[i];
                if (candidate > sell[j]) {
                    sell[j] = candidate;
                }
            }
        }
    }

    int result = sell[k - 1];
    free(buy);
    free(sell);
    
    return result;
}

int main(void) {
    int prices0[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int n0 = (int)(sizeof(prices0) / sizeof(prices0[0]));
    printf("%d\n", maxProfit(1, prices0, n0));

    int prices1[] = {7, 6, 4, 3, 1};
    int n1 = (int)(sizeof(prices1) / sizeof(prices1[0]));
    printf("%d\n", maxProfit(1, prices1, n1));

    int prices2[] = {1, 2};
    int n2 = (int)(sizeof(prices2) / sizeof(prices2[0]));
    printf("%d\n", maxProfit(1, prices2, n2));

    return 0;
}