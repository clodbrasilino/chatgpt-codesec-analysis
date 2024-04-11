#include <stdio.h>

int countChange(int amount, int coins[], int numCoins) {
    int table[amount + 1];
    int i, j;

    for (i = 0; i <= amount; i++)
        table[i] = 0;

    table[0] = 1;

    for (i = 0; i < numCoins; i++)
        for (j = coins[i]; j <= amount; j++)
            table[j] += table[j - coins[i]];

    return table[amount];
}

int main() {
    int coins[] = {1, 2, 5};
    int numCoins = sizeof(coins) / sizeof(coins[0]);
    int amount = 10;

    printf("Number of ways to make change: %d\n", countChange(amount, coins, numCoins));

    return 0;
}