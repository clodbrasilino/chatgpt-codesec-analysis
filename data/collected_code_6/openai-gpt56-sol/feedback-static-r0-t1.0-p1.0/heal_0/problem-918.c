#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int count_coin_change(const size_t coins[],
                             size_t coin_count,
                             size_t amount,
                             uint64_t *result)
{
    uint64_t *ways = NULL;

    if (coins == NULL || coin_count == 0U || result == NULL) {
        return EINVAL;
    }

    if (amount == SIZE_MAX || amount > (SIZE_MAX / sizeof(*ways)) - 1U) {
        return EOVERFLOW;
    }

    ways = calloc(amount + 1U, sizeof(*ways));
    if (ways == NULL) {
        return ENOMEM;
    }

    ways[0] = 1U;

    for (size_t i = 0U; i < coin_count; ++i) {
        if (coins[i] == 0U) {
            free(ways);
            return EINVAL;
        }

        for (size_t j = i + 1U; j < coin_count; ++j) {
            if (coins[i] == coins[j]) {
                free(ways);
                return EINVAL;
            }
        }

        if (coins[i] <= amount) {
            for (size_t value = coins[i]; value <= amount; ++value) {
                if (UINT64_MAX - ways[value] < ways[value - coins[i]]) {
                    free(ways);
                    return EOVERFLOW;
                }
                ways[value] += ways[value - coins[i]];
            }
        }
    }

    *result = ways[amount];
    free(ways);
    return 0;
}

int main(void)
{
    const size_t coins[] = {1U, 2U, 5U};
    const size_t amount = 10U;
    uint64_t result = 0U;
    int status = count_coin_change(
        coins,
        sizeof(coins) / sizeof(coins[0]),
        amount,
        &result
    );

    if (status != 0) {
        errno = status;
        perror("count_coin_change");
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}