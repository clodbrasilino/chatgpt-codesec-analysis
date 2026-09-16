#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

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
            if (coins[j] > 0 && i >= coins[j] && dp[i - coins[j]] != INT_MAX && dp[i - coins[j]] + 1 < dp[i]) {
                dp[i] = dp[i - coins[j]] + 1;
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
    const int coins[] = {9, 6, 5, 1};
    int numCoins = sizeof(coins) / sizeof(coins[0]);
    int value = 11;

    int result = minCoins(coins, numCoins, value);
    
    printf("%d\n", result);

    return 0;
}