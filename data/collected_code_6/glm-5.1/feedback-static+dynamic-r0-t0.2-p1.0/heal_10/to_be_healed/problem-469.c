#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 2, got 0
  *  test case 1 failed: expected 7, got 0
  *  test case 0 failed: expected 10, got 5
  */

int maxProfit(int k, const int* prices, int pricesSize) {
    if (k <= 0 || pricesSize <= 1) {
        return 0;
    }

    if (k >= pricesSize / 2) {
        int profit = 0;
        for (int i = 1; i < pricesSize; i++) {
            if (prices[i] > prices[i - 1]) {
                profit += prices[i] - prices[i - 1];
            }
        }
        return profit;
    }

    int** dp = (int**)malloc(pricesSize * sizeof(int*));
    for (int i = 0; i < pricesSize; i++) {
        dp[i] = (int*)malloc((k + 1) * sizeof(int));
        for (int j = 0; j <= k; j++) {
            dp[i][j] = 0;
        }
    }

    for (int j = 1; j <= k; j++) {
        int max_diff = -prices[0];
        for (int i = 1; i < pricesSize; i++) {
            if (prices[i] + max_diff > dp[i - 1][j]) {
                dp[i][j] = prices[i] + max_diff;
            } else {
                dp[i][j] = dp[i - 1][j];
            }
            if (-prices[i] + dp[i][j - 1] > max_diff) {
                max_diff = -prices[i] + dp[i][j - 1];
            }
        }
    }

    int result = dp[pricesSize - 1][k];
    for (int i = 0; i < pricesSize; i++) {
        free(dp[i]);
    }
    free(dp);
    return result;
}

int main() {
    int prices1[] = {3, 2, 6, 5, 0, 3};
    int k1 = 2;
    int size1 = sizeof(prices1) / sizeof(prices1[0]);
    printf("%d\n", maxProfit(k1, prices1, size1));

    int prices2[] = {1, 2, 3, 4, 5};
    int k2 = 2;
    int size2 = sizeof(prices2) / sizeof(prices2[0]);
    printf("%d\n", maxProfit(k2, prices2, size2));

    int prices3[] = {7, 6, 4, 3, 1};
    int k3 = 2;
    int size3 = sizeof(prices3) / sizeof(prices3[0]);
    printf("%d\n", maxProfit(k3, prices3, size3));

    return 0;
}