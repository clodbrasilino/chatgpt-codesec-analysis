#include <stdio.h>
#include <stdlib.h>

long long delannoy_number(int n, int m) {
    if (n < 0 || m < 0) return -1;
    long long dp[n+1][m+1];
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = 1;
            } else {
                /* Possible weaknesses found:
                 * UBSan: signed integer overflow: 9005397880840948770 + 823085665657348455 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000002,time:2543,execs:680,op:havoc,rep:5)
                 * UBSan: signed integer overflow: 2949761933621924029 + 7758352922652586893 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000002,time:2543,execs:680,op:havoc,rep:5)
                 */
                dp[i][j] = dp[i-1][j] + dp[i][j-1] + dp[i-1][j-1];
            }
        }
    }
    return dp[n][m];
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000001,sig:06,src:000002,time:822,execs:179,op:havoc,rep:7; likely memory-safety defect
  */

int main() {
    int n, m;
    printf("Enter n and m: ");
    scanf("%d %d", &n, &m);
    if (n < 0 || m < 0) {
        printf("Both n and m must be non-negative.\n");
        return 1;
    }
    long long result = delannoy_number(n, m);
    printf("The Delannoy number D(%d, %d) is: %lld\n", n, m, result);
    return 0;
}