#include <stdio.h>

int countChange(int amount, int coins[], int n) {
    if (amount == 0)
        return 1;
    if (amount < 0 || n == 0)
        return 0;
    return countChange(amount, coins, n - 1) + countChange(amount - coins[n - 1], coins, n);
}

int main() {
    int coins[] = {1, 2, 5};
    int amount = 10;
    int n = sizeof(coins) / sizeof(coins[0]);
    printf("Total ways to make change: %d\n", countChange(amount, coins, n));
    return 0;
}