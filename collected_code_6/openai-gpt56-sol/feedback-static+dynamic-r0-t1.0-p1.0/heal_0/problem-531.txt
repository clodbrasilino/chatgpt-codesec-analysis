#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static int minimum_coins(const int coins[], size_t count, int value, int *result)
{
    int *minimum;
    size_t i;
    int amount;

    if (coins == NULL || result == NULL || count == 0U || value < 0) {
        return -1;
    }

    if ((size_t)value > (SIZE_MAX / sizeof(*minimum)) - 1U) {
        return -1;
    }

    minimum = malloc(((size_t)value + 1U) * sizeof(*minimum));
    if (minimum == NULL) {
        return -1;
    }

    minimum[0] = 0;

    for (amount = 1; amount <= value; ++amount) {
        minimum[amount] = INT_MAX;
    }

    for (amount = 1; amount <= value; ++amount) {
        for (i = 0U; i < count; ++i) {
            if (coins[i] <= 0) {
                free(minimum);
                return -1;
            }

            if (coins[i] <= amount &&
                minimum[amount - coins[i]] != INT_MAX &&
                minimum[amount - coins[i]] < INT_MAX - 1) {
                int candidate = minimum[amount - coins[i]] + 1;

                if (candidate < minimum[amount]) {
                    minimum[amount] = candidate;
                }
            }
        }
    }

    *result = minimum[value] == INT_MAX ? -1 : minimum[value];
    free(minimum);
    return 0;
}

int main(void)
{
    const int coins[] = {1, 3, 4};
    const int value = 6;
    int result;

    if (minimum_coins(coins, sizeof(coins) / sizeof(coins[0]), value, &result) != 0) {
        fputs("Failed to calculate the minimum number of coins.\n", stderr);
        return EXIT_FAILURE;
    }

    if (result < 0) {
        printf("The value %d cannot be formed with the given coins.\n", value);
    } else {
        printf("Minimum number of coins: %d\n", result);
    }

    return EXIT_SUCCESS;
}