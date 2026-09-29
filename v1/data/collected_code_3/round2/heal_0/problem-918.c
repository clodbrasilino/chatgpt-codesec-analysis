#include <stdio.h>

int countChange(int amount, int coins[], int numCoins) {
    int table[amount + 1];
    memset(table, 0, sizeof(table));
    table[0] = 1;

    for(int i = 0; i < numCoins; i++)
        for(int j = coins[i]; j <= amount; j++)
            table[j] += table[j - coins[i]];

    return table[amount];
}

int main() {
    int coins[] = {1, 2, 5, 10, 20, 50, 100, 200};
    int amount = 300;
    int numCoins = sizeof(coins)/sizeof(coins[0]);
    printf("Total number of ways to make change: %d\n", countChange(amount, coins, numCoins));
    return 0;
}