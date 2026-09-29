#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 10, got <no output>
  *  test case 2 failed: expected 2, got <no output>
  *  test case 1 failed: expected 7, got <no output>
  */

int maxProfit(int k, const int* prices, int pricesSize) {
    if (pricesSize <= 1 || k <= 0) {
        return 0;
    }

    if (k >= pricesSize / 2) {
        int max_profit = 0;
        for (int i = 1; i < pricesSize; i++) {
            if (prices[i] > prices[i - 1]) {
                max_profit += prices[i] - prices[i - 1];
            }
        }
        return max_profit;
    }

    int* dp = (int*)calloc(pricesSize, sizeof(int));
    if (dp == NULL) {
        return -1;
    }

    for (int i = 1; i <= k; i++) {
        int max_diff = -prices[0];
        for (int j = 1; j < pricesSize; j++) {
            int prev_dp = dp[j];
            
            int curr_profit = prices[j] + max_diff;
            if (dp[j - 1] > curr_profit) {
                dp[j] = dp[j - 1];
            } else {
                dp[j] = curr_profit;
            }

            int diff = prev_dp - prices[j];
            if (diff > max_diff) {
                max_diff = diff;
            }
        }
    }

    int result = dp[pricesSize - 1];
    free(dp);

    return result;
}

int main(void) {
    int k;
    if (scanf("%d", &k) != 1) {
        return 0;
    }

    int capacity = 1000;
    int* prices = (int*)malloc(capacity * sizeof(int));
    int pricesSize = 0;
    int val;

    while (scanf("%d", &val) == 1) {
        if (pricesSize >= capacity) {
            capacity *= 2;
            /* Possible weaknesses found:
             *  Common realloc mistake: 'prices' nulled but not freed upon failure [memleakOnRealloc]
             */
            prices = (int*)realloc(prices, capacity * sizeof(int));
        }
        prices[pricesSize++] = val;
    }

    int profit = maxProfit(k, prices, pricesSize);
    printf("%d\n", profit);
    
    free(prices);
    return 0;
}