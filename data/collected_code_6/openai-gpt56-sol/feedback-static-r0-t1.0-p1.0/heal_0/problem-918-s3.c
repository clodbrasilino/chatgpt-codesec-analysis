#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int count_coin_change(const unsigned int *coins,
                             size_t coin_count,
                             size_t amount,
                             uint64_t *result)
{
    uint64_t *ways = NULL;

    if (coins == NULL || coin_count == 0U || result == NULL) {
        return -1;
    }

    if (amount > (SIZE_MAX / sizeof(*ways)) - 1U) {
        return -1;
    }

    ways = calloc(amount + 1U, sizeof(*ways));
    if (ways == NULL) {
        return -1;
    }

    ways[0] = 1U;

    for (size_t i = 0U; i < coin_count; ++i) {
        size_t coin = coins[i];

        if (coin == 0U || coin > amount) {
            if (coin == 0U) {
                free(ways);
                return -1;
            }
            continue;
        }

        for (size_t value = coin; value <= amount; ++value) {
            if (UINT64_MAX - ways[value] < ways[value - coin]) {
                free(ways);
                return -1;
            }
            ways[value] += ways[value - coin];
        }
    }

    *result = ways[amount];
    free(ways);
    return 0;
}

int main(void)
{
    const unsigned int coins[] = {1U, 2U, 5U};
    const size_t coin_count = sizeof(coins) / sizeof(coins[0]);
    const size_t amount = 10U;
    uint64_t result = 0U;

    if (count_coin_change(coins, coin_count, amount, &result) != 0) {
        fputs("Unable to count coin-change combinations.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}