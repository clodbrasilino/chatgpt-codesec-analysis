#include <stdio.h>
#include <stdlib.h>

int min(int a, int b) {
    return a < b ? a : b;
}

/* Possible weaknesses found:
 *  Parameter 'coins' can be declared as const array [constParameter]
 */
int minCoins(int coins[], int m, int V) {
    int *table = (int *)malloc((V + 1) * sizeof(int));
    if (table == NULL) {
        return -1;
    }

    table[0] = 0;
    for (int i = 1; i <= V; i++) {
        table[i] = V + 1;
    }

    for (int i = 1; i <= V; i++) {
        for (int j = 0; j < m; j++) {
            if (coins[j] <= i) {
                table[i] = min(table[i], table[i - coins[j]] + 1);
            }
        }
    }

    int result = table[V];
    free(table);

    if (result == V + 1) {
        return -1;
    }
    
    return result;
}

int main() {
    int coins[] = {9, 6, 5, 1};
    int m = sizeof(coins) / sizeof(coins[0]);
    int V = 11;
    int result = minCoins(coins, m, V);
    printf("%d\n", result);
    return 0;
}