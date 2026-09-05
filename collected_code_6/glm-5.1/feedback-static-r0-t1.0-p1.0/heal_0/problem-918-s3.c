#include <stdio.h>
#include <stdlib.h>

int count_coin_change(int amount, int *coins, int num_coins) {
    if (amount < 0) {
        return 0;
    }
    if (coins == NULL || num_coins <= 0) {
        return 0;
    }
    int *dp = (int *)malloc((amount + 1) * sizeof(int));
    if (dp == NULL) {
        return 0;
    }
    for (int i = 0; i <= amount; i++) {
        dp[i] = 0;
    }
    dp[0] = 1;
    for (int i = 0; i < num_coins; i++) {
        for (int j = coins[i]; j <= amount; j++) {
            dp[j] += dp[j - coins[i]];
        }
    }
    int result = dp[amount];
    free(dp);
    return result;
}

int main() {
    int coins[] = {1, 2, 5};
    int num_coins = sizeof(coins) / sizeof(coins[0]);
    int amount = 5;
    int ways = count_coin_change(amount, coins, num_coins);
    printf("%d\n", ways);
    return 0;
}