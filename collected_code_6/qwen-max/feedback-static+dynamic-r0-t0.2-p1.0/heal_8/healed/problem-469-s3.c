#include <stdio.h>
#include <limits.h>

int maxProfit(int k, const int* prices, int n) {
    if (n == 0 || k == 0) return 0;
    if (2 * k >= n) {
        int profit = 0;
        for (int i = 1; i < n; i++) {
            if (prices[i] > prices[i - 1]) {
                profit += prices[i] - prices[i - 1];
            }
        }
        return profit;
    }

    int dp[k + 1][n];
    for (int i = 0; i <= k; i++) {
        for (int j = 0; j < n; j++) {
            dp[i][j] = 0;
        }
    }

    for (int i = 1; i <= k; i++) {
        int maxDiff = INT_MIN;
        for (int j = 1; j < n; j++) {
            maxDiff = (maxDiff > dp[i - 1][j - 1] - prices[j - 1]) ? maxDiff : dp[i - 1][j - 1] - prices[j - 1];
            dp[i][j] = (dp[i][j - 1] > prices[j] + maxDiff) ? dp[i][j - 1] : prices[j] + maxDiff;
        }
    }
    return dp[k][n - 1];
}

int main() {
    int prices1[] = {7, 1, 5, 3, 6, 4};
    int n1 = sizeof(prices1) / sizeof(prices1[0]);
    int k1 = 2;
    printf("Maximum profit: %d\n", maxProfit(k1, prices1, n1));

    int prices2[] = {1, 2, 3, 4, 5};
    int n2 = sizeof(prices2) / sizeof(prices2[0]);
    int k2 = 2;
    printf("Maximum profit: %d\n", maxProfit(k2, prices2, n2));

    int prices3[] = {7, 6, 4, 3, 1};
    int n3 = sizeof(prices3) / sizeof(prices3[0]);
    int k3 = 1;
    printf("Maximum profit: %d\n", maxProfit(k3, prices3, n3));

    int prices4[] = {3, 2, 6, 5, 0, 3};
    int n4 = sizeof(prices4) / sizeof(prices4[0]);
    int k4 = 2;
    printf("Maximum profit: %d\n", maxProfit(k4, prices4, n4));

    int prices5[] = {1, 2, 3, 0, 2};
    int n5 = sizeof(prices5) / sizeof(prices5[0]);
    int k5 = 2;
    printf("Maximum profit: %d\n", maxProfit(k5, prices5, n5));

    return 0;
}