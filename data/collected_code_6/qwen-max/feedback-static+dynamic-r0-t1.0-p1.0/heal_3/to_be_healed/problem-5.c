#include <stdio.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 153, got <no output>
  *  test case 2 failed: expected 2131, got <no output>
  *  test case 0 failed: expected 3, got <no output>
  */

int countWays(int n) {
    if (n == 0)
        return 1;
    if (n == 1)
        return 3;
    int dp[n + 1];
    dp[0] = 1;
    dp[1] = 3;
    for (int i = 2; i <= n; ++i) {
        dp[i] = dp[i - 1] + 2 * dp[i - 2];
    }
    return dp[n];
}

int main() {
    int n = 2;
    printf("%d\n", countWays(n));
    return 0;
}