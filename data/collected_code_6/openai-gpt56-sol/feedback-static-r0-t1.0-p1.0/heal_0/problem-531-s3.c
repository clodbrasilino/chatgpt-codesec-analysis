#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

static int minimum_coins(const int *coins, size_t coin_count, int value)
{
    int *dp;
    size_t i;
    int amount;
    int result;

    if (value < 0 || (coin_count > 0 && coins == NULL)) {
        return -1;
    }

    if (value == 0) {
        return 0;
    }

    if (coin_count == 0 || (size_t)value > (SIZE_MAX / sizeof(*dp)) - 1U) {
        return -1;
    }

    dp = malloc(((size_t)value + 1U) * sizeof(*dp));
    if (dp == NULL) {
        return -1;
    }

    dp[0] = 0;

    for (amount = 1; amount <= value; ++amount) {
        dp[amount] = INT_MAX;
    }

    for (amount = 1; amount <= value; ++amount) {
        for (i = 0; i < coin_count; ++i) {
            if (coins[i] > 0 && coins[i] <= amount &&
                dp[amount - coins[i]] != INT_MAX &&
                dp[amount - coins[i]] < INT_MAX - 1) {
                int candidate = dp[amount - coins[i]] + 1;

                if (candidate < dp[amount]) {
                    dp[amount] = candidate;
                }
            }
        }
    }

    result = dp[value] == INT_MAX ? -1 : dp[value];
    free(dp);

    return result;
}

int main(void)
{
    int coins[] = {1, 2, 5};
    size_t coin_count = sizeof(coins) / sizeof(coins[0]);
    int value = 11;
    int result = minimum_coins(coins, coin_count, value);

    if (result < 0) {
        if (fprintf(stdout, "The value cannot be made with the given coins.\n") < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (fprintf(stdout, "Minimum number of coins: %d\n", result) < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}