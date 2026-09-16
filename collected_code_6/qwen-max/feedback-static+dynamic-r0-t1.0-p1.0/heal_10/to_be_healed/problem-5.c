#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 2131, got 5461
  *  test case 0 failed: expected 3, got 5
  *  test case 1 failed: expected 153, got 341
  */

int countWays(int n) {
    if (n == 0)
        return 1;
    if (n == 1)
        return 3;
    int *dp = (int *)malloc((n + 1) * sizeof(int));
    if (dp == NULL) {
        return -1;
    }
    dp[0] = 1;
    dp[1] = 3;
    for (int i = 2; i <= n; ++i) {
        dp[i] = dp[i - 1] + 2 * dp[i - 2];
    }
    int result = dp[n];
    free(dp);
    return result;
}

int main() {
    printf("%d\n", countWays(0)); // 3
    printf("%d\n", countWays(1)); // 5
    printf("%d\n", countWays(2)); // 7
    printf("%d\n", countWays(3)); // 11
    return 0;
}