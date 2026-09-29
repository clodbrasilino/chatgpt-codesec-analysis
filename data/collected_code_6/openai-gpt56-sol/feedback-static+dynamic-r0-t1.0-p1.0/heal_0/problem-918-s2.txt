#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int count_coin_change(const unsigned int *coins, size_t coin_count,
                             unsigned int amount, uint64_t *result)
{
    uint64_t *ways = NULL;
    size_t table_size;

    if (coins == NULL || coin_count == 0U || result == NULL) {
        return -1;
    }

    if ((size_t)amount > (SIZE_MAX / sizeof(*ways)) - 1U) {
        return -1;
    }

    table_size = (size_t)amount + 1U;
    ways = calloc(table_size, sizeof(*ways));
    if (ways == NULL) {
        return -1;
    }

    ways[0] = 1U;

    for (size_t i = 0U; i < coin_count; ++i) {
        if (coins[i] == 0U) {
            free(ways);
            return -1;
        }

        for (size_t value = coins[i]; value <= (size_t)amount; ++value) {
            uint64_t addition = ways[value - coins[i]];

            if (UINT64_MAX - ways[value] < addition) {
                free(ways);
                return -1;
            }

            ways[value] += addition;
        }
    }

    *result = ways[amount];
    free(ways);
    return 0;
}

int main(void)
{
    const unsigned int coins[] = {1U, 2U, 5U};
    const unsigned int amount = 11U;
    const size_t coin_count = sizeof(coins) / sizeof(coins[0]);
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