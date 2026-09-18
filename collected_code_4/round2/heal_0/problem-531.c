#include <stdio.h>
#include <limits.h>

int minCoins(int coins[], int numberOfCoins, int value){
    int table[value+1];

    table[0] = 0;

    for (int i = 1; i <= value; i++)
        table[i] = INT_MAX;

    for (int i = 1; i <= value; i++){
        for (int j = 0; j < numberOfCoins; j++)
          if (coins[j] <= i){
              int subResult = table[i-coins[j]];
              if (subResult != INT_MAX && subResult + 1 < table[i])
                table[i] = subResult + 1;
          }
    }
    return (table[value] == INT_MAX) ? -1 : table[value];
}

int main(void){
    int coins[] = {9, 6, 5, 1};
    int value = 11;
    int numberOfCoins = sizeof(coins)/sizeof(coins[0]);
    printf("Minimum coins required is: %d", minCoins(coins, numberOfCoins, value));
    return 0;
}