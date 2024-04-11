#include <stdio.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'memset'
  */

int countChange(int amount, int coins[], int numCoins) {
    int table[amount + 1];
    /* Possible weaknesses found:
     *  implicit declaration of function 'memset' [-Wimplicit-function-declaration]
     *  incompatible implicit declaration of built-in function 'memset' [-Wbuiltin-declaration-mismatch]
     *  include '<string.h>' or provide a declaration of 'memset'
     */
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