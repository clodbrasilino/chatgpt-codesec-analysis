#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 7, got 0
  *  test case 0 failed: expected 10, got 5
  *  test case 2 failed: expected 2, got 0
  */

int maxProfit(int k, const int *prices, int n)
{
    int i;
    int j;
    int result;
    int *buy;
    int *sell;

    if (prices == NULL || n <= 1 || k <= 0) {
        return 0;
    }

    if (k > n / 2) {
        result = 0;
        for (i = 1; i < n; i++) {
            if (prices[i] > prices[i - 1]) {
                result += prices[i] - prices[i - 1];
            }
        }
        return result;
    }

    buy = malloc((size_t)(k + 1) * sizeof(int));
    if (buy == NULL) {
        return -1;
    }

    sell = malloc((size_t)(k + 1) * sizeof(int));
    if (sell == NULL) {
        free(buy);
        return -1;
    }

    for (j = 0; j <= k; j++) {
        buy[j] = INT_MIN;
        sell[j] = 0;
    }

    for (i = 0; i < n; i++) {
        for (j = 1; j <= k; j++) {
            if (sell[j - 1] - prices[i] > buy[j]) {
                buy[j] = sell[j - 1] - prices[i];
            }
            if (buy[j] != INT_MIN && buy[j] + prices[i] > sell[j]) {
                sell[j] = buy[j] + prices[i];
            }
        }
    }

    result = sell[k];

    free(buy);
    free(sell);

    return result;
}

int main(void)
{
    int prices[] = {3, 2, 6, 5, 0, 3};
    int n = (int)(sizeof(prices) / sizeof(prices[0]));
    int k = 2;
    int profit;

    profit = maxProfit(k, prices, n);
    if (profit < 0) {
        fprintf(stderr, "Error: memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Maximum profit with at most %d transactions: %d\n", k, profit);

    return EXIT_SUCCESS;
}