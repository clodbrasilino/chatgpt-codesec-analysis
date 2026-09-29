#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>

int minimum_coins(const int *coins, size_t coin_count, int value)
{
    int *dp;
    size_t i;
    int amount;
    int result;

    if (coins == NULL || coin_count == 0U || value < 0) {
        return -1;
    }

    if ((size_t)value > (SIZE_MAX / sizeof(*dp)) - 1U) {
        return -1;
    }

    dp = malloc(((size_t)value + 1U) * sizeof(*dp));
    if (dp == NULL) {
        return -1;
    }

    dp[0] = 0;

    for (amount = 1; amount <= value; ++amount) {
        dp[amount] = value + 1;

        for (i = 0U; i < coin_count; ++i) {
            if (coins[i] <= 0) {
                free(dp);
                return -1;
            }

            if (coins[i] <= amount && dp[amount - coins[i]] != value + 1) {
                int candidate = dp[amount - coins[i]] + 1;

                if (candidate < dp[amount]) {
                    dp[amount] = candidate;
                }
            }
        }
    }

    result = (dp[value] == value + 1) ? -1 : dp[value];
    free(dp);

    return result;
}

int main(void)
{
    int coins[] = {1, 2, 5};
    const size_t coin_count = sizeof(coins) / sizeof(coins[0]);
    int value;
    int result;

    if (printf("Enter the value: ") < 0) {
        return EXIT_FAILURE;
    }

    if (scanf("%d", &value) != 1 || value < 0) {
        fprintf(stderr, "Invalid value\n");
        return EXIT_FAILURE;
    }

    result = minimum_coins(coins, coin_count, value);

    if (result < 0) {
        if (printf("The value cannot be formed with the available coins.\n") < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("Minimum number of coins: %d\n", result) < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}