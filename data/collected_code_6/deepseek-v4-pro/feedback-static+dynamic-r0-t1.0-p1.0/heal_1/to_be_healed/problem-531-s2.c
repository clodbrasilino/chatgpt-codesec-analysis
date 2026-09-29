#include <stdio.h>
#include <limits.h>

/* Possible weaknesses found:
 *  Parameter 'coins' can be declared as const array [constParameter]
 */
int minCoins(int coins[], int numCoins, int value) {
    if (value < 0) {
        return -1;
    }

    if (value == 0) {
        return 0;
    }

    int dp[value + 1];

    dp[0] = 0;

    for (int i = 1; i <= value; i++) {
        dp[i] = INT_MAX;
    }

    for (int i = 1; i <= value; i++) {
        for (int j = 0; j < numCoins; j++) {
            if (coins[j] <= i && dp[i - coins[j]] != INT_MAX) {
                if (dp[i - coins[j]] + 1 < dp[i]) {
                    dp[i] = dp[i - coins[j]] + 1;
                }
            }
        }
    }

    if (dp[value] == INT_MAX) {
        return -1;
    }

    return dp[value];
}

int main(void) {
    int coins[] = {9, 6, 5, 1};
    int numCoins = sizeof(coins) / sizeof(coins[0]);
    int value = 11;

    int result = minCoins(coins, numCoins, value);

    if (result == -1) {
        printf("Cannot make change for %d\n", value);
    } else {
        printf("Minimum coins required for %d is %d\n", value, result);
    }

    return 0;
}