#include <stdio.h>

int countCoinChange(int coins[], int numCoins, int amount) {
    // Create a 2D array to store the solutions
    int table[amount+1][numCoins];

    // Initialize base case: when amount = 0, there is always 1 solution
    for (int i = 0; i < numCoins; i++) {
        table[0][i] = 1;
    }
    
    // Fill the table in bottom-up manner
    for (int i = 1; i <= amount; i++) {
        for (int j = 0; j < numCoins; j++) {
            // Include coins[j] in the solution
            int includeCoin = (i-coins[j] >= 0) ? table[i-coins[j]][j] : 0;

            // Exclude coins[j] from the solution
            int excludeCoin = (j >= 1) ? table[i][j-1] : 0;

            // Number of solutions is sum of includeCoin and excludeCoin
            table[i][j] = includeCoin + excludeCoin;
        }
    }

    // Return the number of solutions for the given amount
    return table[amount][numCoins-1];
}

int main() {
    int coins[] = {1, 2, 5};  // Available coin denominations
    int numCoins = sizeof(coins) / sizeof(int);  // Number of coin denominations
    int amount = 11;  // Amount for which change needs to be counted

    int numSolutions = countCoinChange(coins, numCoins, amount);

    printf("Number of solutions for amount %d: %d\n", amount, numSolutions);

    return 0;
}