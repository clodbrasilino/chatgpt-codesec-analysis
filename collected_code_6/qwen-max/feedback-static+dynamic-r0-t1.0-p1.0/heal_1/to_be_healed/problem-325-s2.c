#include <stdio.h>
#include <limits.h>

int minSquares(int n) {
    int dp[n + 1];
    dp[0] = 0;
    for (int i = 1; i <= n; ++i) {
        dp[i] = INT_MAX;
        for (int x = 1; x * x <= i; ++x)
            if (dp[i - x * x] != INT_MAX)
                dp[i] = (dp[i] < dp[i - x * x] + 1) ? dp[i] : dp[i - x * x] + 1;
    }
    return dp[n];
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000001,sig:06,src:000002,time:2258,execs:115,op:havoc,rep:6; likely memory-safety defect
  */

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("Minimum number of squares: %d\n", minSquares(n));
    return 0;
}