#include <stdio.h>
#include <limits.h>

/* Possible weaknesses found:
 *  Parameter 'prices' can be declared as pointer to const [constParameterPointer]
 */
int maxProfit(int k, int* prices, int pricesSize) {
    if (pricesSize == 0 || k == 0) return 0;

    if (k > pricesSize / 2) {
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
        dp[i][0] = 0;
    }
    for (int j = 0; j < pricesSize; j++) {
        dp[0][j] = 0;
    }

    for (int i = 1; i <= k; i++) {
        int maxDiff = -prices[0];
        for (int j = 1; j < pricesSize; j++) {
            dp[i][j] = (dp[i][j - 1] > (prices[j] + maxDiff)) ? dp[i][j - 1] : (prices[j] + maxDiff);
            maxDiff = (maxDiff > (dp[i - 1][j - 1] - prices[j])) ? maxDiff : (dp[i - 1][j - 1] - prices[j]);
        }
    }

    return dp[k][pricesSize - 1];
}

int main() {
    int prices[] = {3, 2, 6, 5, 0, 3};
    int pricesSize = sizeof(prices) / sizeof(prices[0]);
    int k = 2;

    int result = maxProfit(k, prices, pricesSize);
    printf("Maximum Profit: %d\n", result);

    return 0;
}