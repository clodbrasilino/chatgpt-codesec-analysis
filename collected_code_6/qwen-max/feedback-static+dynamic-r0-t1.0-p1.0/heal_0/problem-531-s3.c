#include <stdio.h>
#include <limits.h>

int min(int a, int b) {
    return (a < b) ? a : b;
}

int minCoins(int coins[], int m, int V) {
    if (V == 0) return 0;
    int res = INT_MAX; 
    for (int i = 0; i < m; i++) {
        if (coins[i] <= V) {
            int sub_res = minCoins(coins, m, V - coins[i]);
            if (sub_res != INT_MAX && sub_res + 1 < res)
                res = sub_res + 1;
        }
    }
    return res;
}

int main() {
    int coins[] = {9, 6, 5, 1};
    int m = sizeof(coins)/sizeof(coins[0]);
    int V = 11;
    int result = minCoins(coins, m, V);
    printf("Minimum coins required is %d\n", result);
    return 0;
}