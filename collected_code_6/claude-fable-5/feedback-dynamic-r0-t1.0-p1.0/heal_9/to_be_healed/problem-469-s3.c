#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 10, got 5
  *  test case 1 failed: expected 7, got 0
  *  test case 2 failed: expected 2, got 0
  */

int maxProfit(int k, const int *prices, int n)
{
    int *prev;
    int *curr;
    int *tmp;
    int t;
    int d;
    int maxDiff;
    int result;

    if (prices == NULL || n <= 1 || k <= 0) {
        return 0;
    }

    if (k >= n / 2) {
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
        maxDiff = prev[0] - prices[0];
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
    int prices1[] = {10, 22, 5, 75, 65, 80};
    int prices2[] = {3, 2, 6, 5, 0, 3};
    int prices3[] = {2, 4, 1};
    int n1 = (int)(sizeof(prices1) / sizeof(prices1[0]));
    int n2 = (int)(sizeof(prices2) / sizeof(prices2[0]));
    int n3 = (int)(sizeof(prices3) / sizeof(prices3[0]));
    int profit;

    profit = maxProfit(2, prices1, n1);
    printf("Maximum profit with at most %d transactions: %d\n", 2, profit);

    profit = maxProfit(2, prices2, n2);
    printf("Maximum profit with at most %d transactions: %d\n", 2, profit);

    profit = maxProfit(2, prices3, n3);
    printf("Maximum profit with at most %d transactions: %d\n", 2, profit);

    return EXIT_SUCCESS;
}