#include <stdio.h>
 /* Possible weaknesses found:
  *  'INT_MAX' is defined in header '<limits.h>'; did you forget to '#include <limits.h>'?
  */

int  minCoins(int coins[], int numCoins, int target) {
    int dp[target + 1];
    dp[0] = 0;

    for (int i = 1; i <= target; i++) {
        /* Possible weaknesses found:
         *  each undeclared identifier is reported only once for each function it appears in
         *  'INT_MAX' undeclared (first use in this function)
         */
        dp[i] = INT_MAX;
    }

    for (int i = 1; i <= target; i++) {
        for (int j = 0; j < numCoins; j++) {
            /* Possible weaknesses found:
             *  Cannot determine that 'coins[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            if (coins[j] <= i) {
                /* Possible weaknesses found:
                 *  Cannot determine that 'coins[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
                 */
                int sub_res = dp[i - coins[j]];
                if (sub_res != INT_MAX && sub_res + 1 < dp[i]) {
                    dp[i] = sub_res + 1;
                }
            }
        }
    }

    return dp[target];
}

int main() {
    int coins[] = {1, 2, 5};
    int numCoins = sizeof(coins) / sizeof(coins[0]);
    int target = 11;
    int minNumCoins = minCoins(coins, numCoins, target);
    printf("Minimum number of coins needed: %d", minNumCoins);

    return 0;
}