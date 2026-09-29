#include <stdio.h>

#define ARRAY_SIZE(arr) sizeof(arr)/sizeof(arr[0])

int count_coin_changes(int coins[], int coin_size, int amount) {
    int table[amount+1];
    
    table[0] = 1;
    for(int i=1; i<=amount; i++){
        table[i] = 0;
    }

    for(int i=0; i<coin_size; i++){
        for(int j=coins[i]; j<=amount; j++){
            table[j] += table[j-coins[i]];
        }
    }
    return table[amount];
}

int main() {
    int coins[] = {1, 2, 5, 10};
    int amount = 20;

    int coin_size = ARRAY_SIZE(coins);
    printf("%d", count_coin_changes(coins, coin_size, amount));
    return 0;
}