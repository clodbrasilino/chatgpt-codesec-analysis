#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* Possible weaknesses found:
 *  Parameter 'coins' can be declared as const array [constParameter]
 */
int minCoins(int coins[], int n, int value) {
    if (value < 0 || n <= 0 || coins == NULL) {
        return -1;
    }
    
    if (value == 0) {
        return 0;
    }
    
    int *dp = (int *)malloc((value + 1) * sizeof(int));
    if (dp == NULL) {
        return -1;
    }
    
    dp[0] = 0;
    
    for (int i = 1; i <= value; i++) {
        dp[i] = INT_MAX;
    }
    
    for (int i = 1; i <= value; i++) {
        for (int j = 0; j < n; j++) {
            if (coins[j] <= i && dp[i - coins[j]] != INT_MAX) {
                int subResult = dp[i - coins[j]] + 1;
                if (subResult < dp[i]) {
                    dp[i] = subResult;
                }
            }
        }
    }
    
    int result = (dp[value] == INT_MAX) ? -1 : dp[value];
    free(dp);
    dp = NULL;
    
    return result;
}

int main(void) {
    int coins[] = {1, 2, 5, 10, 20, 50, 100};
    int n = sizeof(coins) / sizeof(coins[0]);
    int value = 93;
    
    int result = minCoins(coins, n, value);
    
    if (result == -1) {
        printf("Cannot make value %d with given coins\n", value);
    } else {
        printf("Minimum coins required: %d\n", result);
    }
    
    return 0;
}