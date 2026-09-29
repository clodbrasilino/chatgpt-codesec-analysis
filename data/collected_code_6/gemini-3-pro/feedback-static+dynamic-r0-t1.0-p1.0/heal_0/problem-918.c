#include <stdio.h>
#include <stdlib.h>

long long count_coin_change(int coins[], int num_coins, int amount) {
    if (amount < 0 || num_coins <= 0 || coins == NULL) {
        return 0;
    }

    long long *dp = (long long *)calloc((amount + 1), sizeof(long long));
    if (dp == NULL) {
        return -1;
    }

    dp[0] = 1;

    for (int i = 0; i < num_coins; i++) {
        if (coins[i] <= 0) {
            free(dp);
            return 0;
        }
        for (int j = coins[i]; j <= amount; j++) {
            dp[j] += dp[j - coins[i]];
        }
    }

    long long result = dp[amount];
    free(dp);

    return result;
}

int main() {
    int coins[] = {1, 2, 5};
    int num_coins = sizeof(coins) / sizeof(coins[0]);
    int amount = 11;

    long long ways = count_coin_change(coins, num_coins, amount);

    if (ways == -1) {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    printf("%lld\n", ways);

    return EXIT_SUCCESS;
}