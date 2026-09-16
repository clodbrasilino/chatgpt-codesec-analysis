#include <stdio.h>
#include <limits.h>

int coinChange(const int coins[], int n, int value) {
    int table[value + 1];
    table[0] = 0;
    for (int i = 1; i <= value; i++) {
        table[i] = INT_MAX;
    }
    for (int i = 1; i <= value; i++) {
        for (int j = 0; j < n; j++) {
            if (coins[j] <= i) {
                int sub_res = table[i - coins[j]];
                if (sub_res != INT_MAX && sub_res + 1 < table[i]) {
                    table[i] = sub_res + 1;
                }
            }
        }
    }
    return table[value] == INT_MAX ? -1 : table[value];
}

int main() {
    const int coins[] = {1, 2, 5};
    int n = 3;
    int value = 11;
    printf("Minimum number of coins required: %d\n", coinChange(coins, n, value));
    return 0;
}