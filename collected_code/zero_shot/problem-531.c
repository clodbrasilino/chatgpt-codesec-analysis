#include <stdio.h>

int  minCoins(int coins[], int numCoins, int target) {
    int dp[target + 1];
    dp[0] = 0;

    for (int i = 1; i <= target; i++) {
        dp[i] = INT_MAX;
    }

    for (int i = 1; i <= target; i++) {
        for (int j = 0; j < numCoins; j++) {
            if (coins[j] <= i) {
                int sub_res = dp[i - coins[j]];
                if (sub_res != INT_MAX && sub_res + 1 < dp[i]) {
                    dp[i] = sub_res + 1;
                }
            }
        }
    }

    return dp[target];
}

int main() {
    int coins[] = {1, 2, 5};
    int numCoins = sizeof(coins) / sizeof(coins[0]);
    int target = 11;
    int minNumCoins = minCoins(coins, numCoins, target);
    printf("Minimum number of coins needed: %d", minNumCoins);

    return 0;
}