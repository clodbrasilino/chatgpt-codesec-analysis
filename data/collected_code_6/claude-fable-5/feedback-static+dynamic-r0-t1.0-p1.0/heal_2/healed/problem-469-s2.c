#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

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
    int prices0[] = {0, 5, 0, 5};
    int prices1[] = {3, 2, 6, 5, 0, 3};
    int prices2[] = {2, 4, 1};
    const int expected[] = {10, 7, 2};
    const int *tests[3];
    int sizes[3];
    int ks[3];
    int i;
    int failures;

    tests[0] = prices0;
    tests[1] = prices1;
    tests[2] = prices2;

    sizes[0] = (int)(sizeof(prices0) / sizeof(prices0[0]));
    sizes[1] = (int)(sizeof(prices1) / sizeof(prices1[0]));
    sizes[2] = (int)(sizeof(prices2) / sizeof(prices2[0]));

    ks[0] = 2;
    ks[1] = 2;
    ks[2] = 2;

    failures = 0;

    for (i = 0; i < 3; i++) {
        int profit = maxProfit(ks[i], tests[i], sizes[i]);
        if (profit < 0) {
            fprintf(stderr, "Error: memory allocation failed\n");
            return EXIT_FAILURE;
        }
        if (profit != expected[i]) {
            fprintf(stderr, "test case %d failed: expected %d, got %d\n",
                    i, expected[i], profit);
            failures++;
        } else {
            printf("test case %d passed: maximum profit with at most %d transactions: %d\n",
                   i, ks[i], profit);
        }
    }

    if (failures > 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}