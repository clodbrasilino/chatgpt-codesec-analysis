#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected 7, got 0
  *  test case 2 failed: expected 2, got 0
  *  test case 0 failed: expected 10, got 5
  */

/* Possible weaknesses found:
 *  Parameter 'prices' can be declared as pointer to const [constParameterPointer]
 */
int maxProfit(int k, int* prices, int pricesSize) {
    if (pricesSize == 0 || k == 0) {
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

    int** dp = (int**)malloc((k + 1) * sizeof(int*));
    if (dp == NULL) {
        return -1;
    }
    
    for (int i = 0; i <= k; i++) {
        dp[i] = (int*)calloc(pricesSize, sizeof(int));
        if (dp[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(dp[j]);
            }
            free(dp);
            return -1;
        }
    }

    for (int i = 1; i <= k; i++) {
        int maxDiff = -prices[0];
        for (int j = 1; j < pricesSize; j++) {
            dp[i][j] = max(dp[i][j - 1], prices[j] + maxDiff);
            maxDiff = max(maxDiff, dp[i - 1][j] - prices[j]);
        }
    }

    int result = dp[k][pricesSize - 1];

    for (int i = 0; i <= k; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}

int main() {
    int prices[] = {3, 2, 6, 5, 0, 3};
    int k = 2;
    int pricesSize = sizeof(prices) / sizeof(prices[0]);

    int profit = maxProfit(k, prices, pricesSize);
    if (profit != -1) {
        printf("%d\n", profit);
    } else {
        printf("Memory allocation failed\n");
    }

    return 0;
}