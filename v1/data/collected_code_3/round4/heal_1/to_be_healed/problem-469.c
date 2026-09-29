#include <stdio.h>
#include <stdlib.h>

int maxProfit(int k, int n, int prices[]) {
    if (k == 0 || n == 0) {
        return 0;
    }

    if (k > n / 2) {
        int profit = 0;
        for (int i = 1; i < n; i++) {
            if (prices[i] > prices[i - 1]) {
                profit += prices[i] - prices[i - 1];
            }
        }
        return profit;
    }

    int **dp = (int **)malloc((k + 1) * sizeof(int *));
    for (int i = 0; i <= k; i++) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'dp' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        dp[i] = (int *)malloc((n + 1) * sizeof(int));
    }

    for (int i = 0; i <= k; i++) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL '*dp_104 + _32' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        dp[i][0] = 0;
    }

    for (int j = 0; j <= n; j++) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'dp' [CWE-690] [-Wanalyzer-possible-null-dereference]
         *  use of uninitialized value '*dp' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
         */
        dp[0][j] = 0;
    }

    for (int i = 1; i <= k; i++) {
        int maxDiff = -prices[0];
        for (int j = 1; j < n; j++) {
            dp[i][j] = dp[i][j - 1] > (prices[j] + maxDiff) ? dp[i][j - 1] : (prices[j] + maxDiff);
            maxDiff = maxDiff > (dp[i - 1][j] - prices[j]) ? maxDiff : (dp[i - 1][j] - prices[j]);
        }
    }

    /* Possible weaknesses found:
     *  use of uninitialized value '*dp_104 + _77' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
     *  use of uninitialized value '*_79 + _82' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
     */
    return dp[k][n - 1];
}

int main() {
    int prices[] = {3, 2, 6, 5, 0, 3};
    int n = sizeof(prices) / sizeof(prices[0]);
    int k = 2;
    printf("Maximum profit is %d", maxProfit(k, n, prices));
    return 0;
}