#include <stdio.h>
#include <limits.h>

int maxProfit(int k, const int* prices, int pricesSize) {
    if (pricesSize == 0 || k == 0) return 0;

    if (k >= pricesSize / 2) {
        int profit = 0;
        for (int i = 1; i < pricesSize; i++) {
            if (prices[i] > prices[i - 1]) {
                profit += prices[i] - prices[i - 1];
            }
        }
        return profit;
    }

    int dp[k + 1][pricesSize];
    for (int i = 0; i <= k; i++) {
        for (int j = 0; j < pricesSize; j++) {
            dp[i][j] = 0;
        }
    }

    for (int i = 1; i <= k; i++) {
        int maxDiff = INT_MIN;
        for (int j = 1; j < pricesSize; j++) {
            maxDiff = (maxDiff > (dp[i - 1][j - 1] - prices[j])) ? maxDiff : (dp[i - 1][j - 1] - prices[j]);
            dp[i][j] = (dp[i][j - 1] > (prices[j] + maxDiff)) ? dp[i][j - 1] : (prices[j] + maxDiff);
        }
    }

    return dp[k][pricesSize - 1];
}

int main() {
    const int prices1[] = {1, 2, 3, 0, 2};
    int pricesSize1 = sizeof(prices1) / sizeof(prices1[0]);
    int k1 = 2;
    int result1 = maxProfit(k1, prices1, pricesSize1);
    printf("Maximum Profit: %d\n", result1);

    const int prices2[] = {1, 2, 3, 4, 5};
    int pricesSize2 = sizeof(prices2) / sizeof(prices2[0]);
    int k2 = 2;
    int result2 = maxProfit(k2, prices2, pricesSize2);
    printf("Maximum Profit: %d\n", result2);

    const int prices3[] = {7, 6, 4, 3, 1};
    int pricesSize3 = sizeof(prices3) / sizeof(prices3[0]);
    int k3 = 1;
    int result3 = maxProfit(k3, prices3, pricesSize3);
    printf("Maximum Profit: %d\n", result3);

    return 0;
}