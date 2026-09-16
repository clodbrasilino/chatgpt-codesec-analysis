#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 7, got <no output>
  *  test case 2 failed: expected 2, got <no output>
  *  test case 0 failed: expected 10, got <no output>
  */

static int maxProfit(int k, const int *prices, int pricesSize)
{
    int *buy;
    int *sell;

    if (prices == NULL || pricesSize < 2 || k <= 0) {
        return 0;
    }

    if (k >= pricesSize / 2) {
        int profit = 0;
        for (int i = 1; i < pricesSize; ++i) {
            if (prices[i] > prices[i - 1]) {
                profit += prices[i] - prices[i - 1];
            }
        }
        return profit;
    }

    buy = malloc(((size_t)k + 1U) * sizeof *buy);
    if (buy == NULL) {
        return 0;
    }

    sell = calloc((size_t)k + 1U, sizeof *sell);
    if (sell == NULL) {
        free(buy);
        buy = NULL;
        return 0;
    }

    for (int j = 0; j <= k; ++j) {
        buy[j] = INT_MIN;
    }

    for (int i = 0; i < pricesSize; ++i) {
        for (int j = k; j >= 1; --j) {
            if (buy[j] < sell[j - 1] - prices[i]) {
                buy[j] = sell[j - 1] - prices[i];
            }
            if (buy[j] != INT_MIN && sell[j] < buy[j] + prices[i]) {
                sell[j] = buy[j] + prices[i];
            }
        }
    }

    {
        int result = sell[k];
        free(sell);
        free(buy);
        sell = NULL;
        buy = NULL;
        return result;
    }
}

int main(void)
{
    int k;
    int n;
    int *prices;

    if (scanf("%d", &k) != 1 || k < 0) {
        fprintf(stderr, "Error: invalid number of transactions\n");
        return EXIT_FAILURE;
    }

    if (scanf("%d", &n) != 1 || n < 0 || n > 100000) {
        fprintf(stderr, "Error: invalid number of prices\n");
        return EXIT_FAILURE;
    }

    prices = NULL;
    if (n > 0) {
        prices = malloc((size_t)n * sizeof *prices);
        if (prices == NULL) {
            fprintf(stderr, "Error: memory allocation failed\n");
            return EXIT_FAILURE;
        }

        for (int i = 0; i < n; ++i) {
            if (scanf("%d", &prices[i]) != 1 || prices[i] < 0 || prices[i] > 10000) {
                fprintf(stderr, "Error: invalid price value\n");
                free(prices);
                prices = NULL;
                return EXIT_FAILURE;
            }
        }
    }

    {
        int result = maxProfit(k, prices, n);
        printf("%d\n", result);
    }

    free(prices);
    prices = NULL;
    return EXIT_SUCCESS;
}