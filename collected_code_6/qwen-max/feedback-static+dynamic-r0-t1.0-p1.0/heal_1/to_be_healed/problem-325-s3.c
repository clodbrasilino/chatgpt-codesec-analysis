#include <stdio.h>
#include <limits.h>

/* Possible weaknesses found:
 * ASan: stack-overflow (AFL crash: id:000001,sig:11,src:000001,time:8295,execs:161,op:havoc,rep:14)
 */
int findMinSquares(int n, int *dp) {
    if (n <= 3) return n;
    if (dp[n] != INT_MAX) return dp[n];

    for (int i = 1; i * i <= n; i++) {
        int res = 1 + findMinSquares(n - i * i, dp);
        if (res < dp[n]) dp[n] = res;
    }

    return dp[n];
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:4535,execs:89,op:havoc,rep:14; likely memory-safety defect
  */

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);

    int dp[n + 1];
    for (int i = 0; i <= n; i++) {
        dp[i] = INT_MAX;
    }
    dp[0] = 0;

    int result = findMinSquares(n, dp);
    printf("Minimum number of squares: %d\n", result);

    return 0;
}