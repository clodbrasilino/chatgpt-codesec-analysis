#include <stdio.h>
#include <stdlib.h>

int count_coin_change(int coins[], int num_coins, int amount) {
    int *dp = (int *)calloc(amount + 1, sizeof(int));
    if (dp == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    
    dp[0] = 1;
    
    for (int i = 0; i < num_coins; i++) {
        for (int j = coins[i]; j <= amount; j++) {
            dp[j] += dp[j - coins[i]];
        }
    }
    
    int result = dp[amount];
    free(dp);
    return result;
}

int main(void) {
    int coins[] = {1, 2, 5};
    int num_coins = sizeof(coins) / sizeof(coins[0]);
    int amount = 11;
    
    int ways = count_coin_change(coins, num_coins, amount);
    printf("Number of ways to make change: %d\n", ways);
    
    return 0;
}