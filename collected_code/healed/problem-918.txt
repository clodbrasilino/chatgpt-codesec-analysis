#include <stdio.h>

int countCoinChange(const int coins[], const int numCoins, const int amount) {
    int table[amount+1][numCoins];

    for (int i = 0; i < numCoins; i++) {
        table[0][i] = 1;
    }
    
    for (int i = 1; i <= amount; i++) {
        for (int j = 0; j < numCoins; j++) {
            int includeCoin = (i-coins[j] >= 0) ? table[i-coins[j]][j] : 0;
            int excludeCoin = (j >= 1) ? table[i][j-1] : 0;
            table[i][j] = includeCoin + excludeCoin;
        }
    }

    return table[amount][numCoins-1];
}

int main() {
    const int coins[] = {1, 2, 5};
    const int numCoins = sizeof(coins) / sizeof(int);
    const int amount = 11;
    int numSolutions = countCoinChange(coins, numCoins, amount);
    printf("Number of solutions for amount %d: %d\n", amount, numSolutions);
    return 0;
}