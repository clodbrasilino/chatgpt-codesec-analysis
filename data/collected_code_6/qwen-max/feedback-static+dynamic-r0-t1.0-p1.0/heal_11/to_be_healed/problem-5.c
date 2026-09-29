#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 3, got 4
  *  test case 1 failed: expected 153, got 76
  *  test case 2 failed: expected 2131, got 521
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
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    int result = dp[n];
    free(dp);
    return result;
}

int main() {
    printf("%d\n", countWays(0)); // 1
    printf("%d\n", countWays(1)); // 3
    printf("%d\n", countWays(2)); // 4
    printf("%d\n", countWays(3)); // 7
    return 0;
}