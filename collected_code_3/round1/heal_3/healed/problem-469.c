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

    int **dp = (int **)calloc((k + 1), sizeof(int *));
    if (!dp) {
        return 0;
    }

    for (int i = 0; i <= k; i++) {
        dp[i] = (int *)calloc((n + 1), sizeof(int));
        if (!dp[i]) {
            for(int j = 0; j <= i; j++) {
                free(dp[j]);
            }
            free(dp);
            return 0;
        }
    }

    for (int i = 1; i <= k; i++) {
        int maxDiff = -prices[0];
        for (int j = 1; j < n; j++) {
            dp[i][j] = dp[i][j - 1] > (prices[j] + maxDiff) ? dp[i][j - 1] : (prices[j] + maxDiff);
            maxDiff = maxDiff > (dp[i - 1][j] - prices[j]) ? maxDiff : (dp[i - 1][j] - prices[j]);
        }
    }

    int result = dp[k][n - 1];
    
    for(int i = 0; i <= k; i++) {
        free(dp[i]);
    }
    free(dp);
    return result;
}

int main() {
    int prices[] = {3, 2, 6, 5, 0, 3};
    int n = sizeof(prices) / sizeof(prices[0]);
    int k = 2;
    printf("Maximum profit is %d", maxProfit(k, n, prices));
    return 0;
}