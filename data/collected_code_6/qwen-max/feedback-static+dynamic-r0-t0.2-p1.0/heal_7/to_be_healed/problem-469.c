#include <stdio.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 7, got 0
  *  test case 0 failed: expected 10, got 5
  *  test case 2 failed: expected 2, got 0
  */

int maxProfit(int k, const int* prices, int n) {
    if (n == 0 || k == 0) return 0;

    if (k >= n / 2) {
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
            dp[i][j] = (dp[i][j - 1] > prices[j] + maxDiff) ? dp[i][j - 1] : prices[j] + maxDiff;
            maxDiff = (maxDiff > dp[i - 1][j] - prices[j]) ? maxDiff : dp[i - 1][j] - prices[j];
        }
    }
    return dp[k][n - 1];
}

int main() {
    int k1 = 2;
    int prices1[] = {2, 4, 1, 5, 7, 3, 6};
    int n1 = sizeof(prices1) / sizeof(prices1[0]);
    printf("Maximum profit: %d\n", maxProfit(k1, prices1, n1));

    int k2 = 1;
    int prices2[] = {7, 1, 5, 3, 6, 4};
    int n2 = sizeof(prices2) / sizeof(prices2[0]);
    printf("Maximum profit: %d\n", maxProfit(k2, prices2, n2));

    int k3 = 1;
    int prices3[] = {7, 6, 4, 3, 1};
    int n3 = sizeof(prices3) / sizeof(prices3[0]);
    printf("Maximum profit: %d\n", maxProfit(k3, prices3, n3));

    return 0;
}