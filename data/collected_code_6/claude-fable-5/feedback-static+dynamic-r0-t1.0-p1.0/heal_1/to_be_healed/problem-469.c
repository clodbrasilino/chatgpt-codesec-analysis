#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int max_int(int a, int b)
{
    return (a > b) ? a : b;
}
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
    int **dp;

    if (prices == NULL || n <= 1 || k <= 0) {
        return 0;
    }

    if (k >= n / 2) {
        result = 0;
        for (i = 1; i < n; i++) {
            if (prices[i] > prices[i - 1]) {
                result += prices[i] - prices[i - 1];
            }
        }
        return result;
    }

    dp = (int **)malloc((size_t)(k + 1) * sizeof(int *));
    if (dp == NULL) {
        return -1;
    }

    for (i = 0; i <= k; i++) {
        dp[i] = (int *)calloc((size_t)n, sizeof(int));
        if (dp[i] == NULL) {
            for (j = 0; j < i; j++) {
                free(dp[j]);
            }
            free(dp);
            return -1;
        }
    }

    for (i = 1; i <= k; i++) {
        int best = -prices[0];
        for (j = 1; j < n; j++) {
            dp[i][j] = max_int(dp[i][j - 1], prices[j] + best);
            best = max_int(best, dp[i - 1][j] - prices[j]);
        }
    }

    result = dp[k][n - 1];

    for (i = 0; i <= k; i++) {
        free(dp[i]);
    }
    free(dp);

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
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Maximum profit with at most %d transactions: %d\n", k, profit);

    return EXIT_SUCCESS;
}