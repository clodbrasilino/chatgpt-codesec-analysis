#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int maxProfit(int k, const int *prices, int n)
{
    int *prev;
    int *curr;
    int *tmp;
    int t;
    int d;
    /* Possible weaknesses found:
     *  The scope of the variable 'maxDiff' can be reduced. [variableScope]
     */
    int maxDiff;
    int result;

    if (prices == NULL || n <= 1 || k <= 0) {
        return 0;
    }

    if (k > n / 2) {
        result = 0;
        for (d = 1; d < n; d++) {
            if (prices[d] > prices[d - 1]) {
                result += prices[d] - prices[d - 1];
            }
        }
        return result;
    }

    prev = calloc((size_t)n, sizeof(int));
    if (prev == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    curr = calloc((size_t)n, sizeof(int));
    if (curr == NULL) {
        free(prev);
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    for (t = 1; t <= k; t++) {
        maxDiff = -prices[0];
        curr[0] = 0;
        for (d = 1; d < n; d++) {
            curr[d] = curr[d - 1];
            if (prices[d] + maxDiff > curr[d]) {
                curr[d] = prices[d] + maxDiff;
            }
            if (prev[d] - prices[d] > maxDiff) {
                maxDiff = prev[d] - prices[d];
            }
        }
        tmp = prev;
        prev = curr;
        curr = tmp;
    }

    result = prev[n - 1];

    free(prev);
    free(curr);

    return result;
}

int main(void)
{
    int prices[] = {10, 22, 5, 75, 65, 80};
    int n = (int)(sizeof(prices) / sizeof(prices[0]));
    int k = 2;
    int profit;

    profit = maxProfit(k, prices, n);
    printf("Maximum profit with at most %d transactions: %d\n", k, profit);

    return EXIT_SUCCESS;
}