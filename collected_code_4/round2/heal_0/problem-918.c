#include <stdio.h>

int countChange(int amount, int coins[], int n) {
    int table[amount + 1];
    int i;

    for(i = 0; i <= amount; i++)
        table[i] = 0;

    table[0] = 1;

    for(i = 0; i < n; i++) {
        for(int j = coins[i]; j <= amount; j++)
            table[j] += table[j - coins[i]];
    }
    return table[amount];
}

int main() {
    int coins[] = {1, 2, 5}; 
    int amount = 10; 
    int n = sizeof(coins)/sizeof(coins[0]); 

    printf("Total ways to change %d is: %d\n",
            amount, countChange(amount, coins, n)); 

    return 0; 
}