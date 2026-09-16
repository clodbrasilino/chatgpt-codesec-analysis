#include <stdio.h>
#include <stdlib.h>

int count_coin_change(int amount, int *coins, int num_coins, int *memo) {
    if (amount < 0) {
        return 0;
    }
    if (amount == 0) {
        return 1;
    }
    if (memo[amount] != -1) {
        return memo[amount];
    }
    int total = 0;
    for (int i = 0; i < num_coins; i++) {
        total += count_coin_change(amount - coins[i], coins + i, num_coins - i, memo);
    }
    memo[amount] = total;
    return total;
}

int count_coin_change_wrapper(int amount, int *coins, int num_coins) {
    if (coins == NULL || num_coins <= 0 || amount < 0) {
        if (amount == 0) return 1;
        return 0;
    }
    int *memo = (int *)malloc((amount + 1) * sizeof(int));
    if (memo == NULL) {
        return 0;
    }
    for (int i = 0; i <= amount; i++) {
        memo[i] = -1;
    }
    int result = count_coin_change(amount, coins, num_coins, memo);
    free(memo);
    return result;
}

int main(void) {
    int coins[] = {1, 2, 5};
    int num_coins = sizeof(coins) / sizeof(coins[0]);
    int amount = 5;
    int result = count_coin_change_wrapper(amount, coins, num_coins);
    printf("%d\n", result);
    return 0;
}