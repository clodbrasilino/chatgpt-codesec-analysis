#include <stdio.h>

int countChange(int amount, int coins[], int numCoins, int index) {
    if (amount == 0) {
        return 1;
    }
    if (amount < 0 || index == numCoins) {
        return 0;
    }
    return countChange(amount - coins[index], coins, numCoins, index) + countChange(amount, coins, numCoins, index + 1);
}

int main() {
    int coins[] = {1, 2, 5};
    int numCoins = sizeof(coins) / sizeof(coins[0]);
    int amount = 10;
    printf("Number of ways to make change: %d\n", countChange(amount, coins, numCoins, 0));
    return 0;
}