#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 7, got 0
  *  test case 2 failed: expected 2, got 0
  *  test case 0 failed: expected 10, got 5
  */

int maxProfit(int k, const int* prices, int n) {
    if (n == 0 || k == 0) return 0;

    if (2 * k > n) {
        int profit = 0;
        for (int i = 1; i < n; i++) {
            if (prices[i] > prices[i - 1]) {
                profit += prices[i] - prices[i - 1];
            }
        }
        return profit;
    }

    int dp[k + 1][n];
    for (int i = 0; i <= k; i++) dp[i][0] = 0;
    for (int j = 0; j < n; j++) dp[0][j] = 0;

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
    int k = 2;
    int prices[] = {3, 2, 6, 5, 0, 3};
    int n = sizeof(prices) / sizeof(prices[0]);
    printf("Maximum profit: %d\n", maxProfit(k, prices, n));

    k = 1;
    int prices2[] = {1, 2, 3};
    n = sizeof(prices2) / sizeof(prices2[0]);
    printf("Maximum profit: %d\n", maxProfit(k, prices2, n));

    k = 2;
    int prices3[] = {2, 4, 1};
    n = sizeof(prices3) / sizeof(prices3[0]);
    printf("Maximum profit: %d\n", maxProfit(k, prices3, n));

    k = 2;
    int prices4[] = {7, 6, 4, 3, 1};
    n = sizeof(prices4) / sizeof(prices4[0]);
    printf("Maximum profit: %d\n", maxProfit(k, prices4, n));

    k = 1;
    int prices5[] = {7, 1, 5, 3, 6, 4};
    n = sizeof(prices5) / sizeof(prices5[0]);
    printf("Maximum profit: %d\n", maxProfit(k, prices5, n));

    k = 2;
    int prices6[] = {3, 3, 5, 0, 0, 3, 1, 4};
    n = sizeof(prices6) / sizeof(prices6[0]);
    printf("Maximum profit: %d\n", maxProfit(k, prices6, n));

    k = 2;
    int prices7[] = {1, 2, 3, 4, 5};
    n = sizeof(prices7) / sizeof(prices7[0]);
    printf("Maximum profit: %d\n", maxProfit(k, prices7, n));

    return 0;
}