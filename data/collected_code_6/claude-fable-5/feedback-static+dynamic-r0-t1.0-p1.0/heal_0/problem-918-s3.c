#include <stdio.h>
#include <stdlib.h>

long long count_coin_change(const int *coins, size_t num_coins, int amount)
{
    long long *table;
    size_t i;
    int j;

    if (coins == NULL || num_coins == 0 || amount < 0) {
        return -1;
    }

    table = calloc((size_t)amount + 1, sizeof(long long));
    if (table == NULL) {
        return -1;
    }

    table[0] = 1;

    for (i = 0; i < num_coins; i++) {
        if (coins[i] <= 0) {
            free(table);
            return -1;
        }
        for (j = coins[i]; j <= amount; j++) {
            table[j] += table[j - coins[i]];
        }
    }

    long long result = table[amount];
    free(table);
    return result;
}

int main(void)
{
    int coins[] = {1, 2, 5};
    size_t num_coins = sizeof(coins) / sizeof(coins[0]);
    int amount = 11;

    long long ways = count_coin_change(coins, num_coins, amount);
    if (ways < 0) {
        fprintf(stderr, "Error computing coin change count\n");
        return EXIT_FAILURE;
    }

    printf("Number of ways to make %d: %lld\n", amount, ways);
    return EXIT_SUCCESS;
}