#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 2, got -1
  *  test case 1 failed: expected 1, got 2
  */

int minCoins(const int coins[], int numCoins, int value) {
    if (value < 0 || numCoins <= 0) {
        return -1;
    }

    int *dp = (int *)malloc((value + 1) * sizeof(int));
    if (dp == NULL) {
        return -1;
    }

    dp[0] = 0;

    for (int i = 1; i <= value; i++) {
        dp[i] = INT_MAX;
        for (int j = 0; j < numCoins; j++) {
            if (coins[j] > 0 && i >= coins[j] && dp[i - coins[j]] != INT_MAX) {
                if (dp[i - coins[j]] + 1 < dp[i]) {
                    dp[i] = dp[i - coins[j]] + 1;
                }
            }
        }
    }

    int result = dp[value];
    free(dp);

    if (result == INT_MAX) {
        return -1;
    }

    return result;
}

int main() {
    const int coins[] = {2, 1};
    int numCoins = sizeof(coins) / sizeof(coins[0]);
    int value = 2;

    int result = minCoins(coins, numCoins, value);
    printf("%d\n", result);

    const int coins2[] = {9, 6, 5, 1};
    int numCoins2 = sizeof(coins2) / sizeof(coins2[0]);
    int value2 = 11;

    int result2 = minCoins(coins2, numCoins2, value2);
    printf("%d\n", result2);

    return 0;
}