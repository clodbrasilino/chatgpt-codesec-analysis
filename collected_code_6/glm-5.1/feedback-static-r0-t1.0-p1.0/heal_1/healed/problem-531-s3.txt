#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int minCoins(const int coins[], int numCoins, int value) {
    if (coins == NULL || numCoins <= 0 || value < 0) {
        return -1;
    }

    int *dp = (int *)malloc((value + 1) * sizeof(int));
    if (dp == NULL) {
        return -1;
    }

    dp[0] = 0;
    for (int i = 1; i <= value; i++) {
        dp[i] = INT_MAX;
    }

    for (int i = 1; i <= value; i++) {
        for (int j = 0; j < numCoins; j++) {
            if (coins[j] > 0 && coins[j] <= i) {
                if (dp[i - coins[j]] != INT_MAX && dp[i - coins[j]] + 1 < dp[i]) {
                    dp[i] = dp[i - coins[j]] + 1;
                }
            }
        }
    }

    int result;
    if (dp[value] == INT_MAX) {
        result = -1;
    } else {
        result = dp[value];
    }

    free(dp);
    return result;
}

int main() {
    int coins[] = {1, 2, 5};
    int numCoins = sizeof(coins) / sizeof(coins[0]);

    int value = 11;
    int result = minCoins(coins, numCoins, value);

    printf("%d\n", result);

    value = 0;
    result = minCoins(coins, numCoins, value);

    printf("%d\n", result);

    value = -5;
    result = minCoins(coins, numCoins, value);

    printf("%d\n", result);

    return 0;
}