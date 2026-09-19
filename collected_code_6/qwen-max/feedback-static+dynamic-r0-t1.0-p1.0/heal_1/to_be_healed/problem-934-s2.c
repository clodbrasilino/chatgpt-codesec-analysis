#include <stdio.h>
#include <stdlib.h>

long long delannoy_number(int n, int m) {
    /* Possible weaknesses found:
     * UBSan: variable length array bound evaluates to non-positive value -1312939255
     * UBSan: variable length array bound evaluates to non-positive value -1180722295 (AFL crash: id:000000,sig:11,src:000001,time:5,execs:15,op:(null),pos:0)
     */
    long long dp[n+1][m+1];
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = 1;
            } else {
                /* Possible weaknesses found:
                 * UBSan: signed integer overflow: 2954578249211727665 + 8052432236270744665 cannot be represented in type 'long long' (AFL crash: id:000003,sig:06,src:000001,time:1652,execs:497,op:havoc,rep:7)
                 * UBSan: signed integer overflow: 9179926484169578570 + 1461164546692490355 cannot be represented in type 'long long' (AFL crash: id:000003,sig:06,src:000001,time:1652,execs:497,op:havoc,rep:7)
                 */
                dp[i][j] = dp[i-1][j] + dp[i][j-1] + dp[i-1][j-1];
            }
        }
    }
    return dp[n][m];
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000001,sig:06,src:000001,time:426,execs:105,op:arith8,pos:1,val:+35; likely memory-safety defect
  */

int main() {
    int n, m;
    printf("Enter n and m: ");
    scanf("%d %d", &n, &m);
    long long result = delannoy_number(n, m);
    printf("The Delannoy number D(%d, %d) is: %lld\n", n, m, result);
    return 0;
}