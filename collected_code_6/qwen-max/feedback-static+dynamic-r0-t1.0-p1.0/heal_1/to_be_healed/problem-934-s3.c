#include <stdio.h>
#include <stdlib.h>

int delannoy(int n, int m) {
    if (n == 0 || m == 0) return 1;
    /* Possible weaknesses found:
     * UBSan: variable length array bound evaluates to non-positive value -443 (AFL crash: id:000003,sig:06,src:000005,time:2871,execs:1303,op:havoc,rep:4)
     */
    int dp[n+1][m+1];
    for (int i = 0; i < n + 1; ++i) {
        for (int j = 0; j < m + 1; ++j) {
            if (i == 0 || j == 0) {
                dp[i][j] = 1;
            } else {
                /* Possible weaknesses found:
                 * UBSan: signed integer overflow: 2120032959 + 57833729 cannot be represented in type 'int' (AFL crash: id:000002,sig:06,src:000005,time:1800,execs:818,op:havoc,rep:1)
                 * UBSan: signed integer overflow: 2145987825 + 606639529 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000003,time:1045,execs:473,op:havoc,rep:2)
                 * UBSan: signed integer overflow: 2075383782 + 131489289 cannot be represented in type 'int' (AFL crash: id:000002,sig:06,src:000005,time:1800,execs:818,op:havoc,rep:1)
                 * UBSan: signed integer overflow: 2049630600 + 179861305 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000003,time:1045,execs:473,op:havoc,rep:2)
                 */
                dp[i][j] = dp[i-1][j] + dp[i][j-1] + dp[i-1][j-1];
            }
        }
    }
    return dp[n][m];
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000003,time:975,execs:443,op:havoc,rep:4; likely memory-safety defect
  */

int main() {
    int n, m;
    printf("Enter n and m: ");
    if (scanf("%d %d", &n, &m) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    printf("Delannoy number D(%d, %d) is %d\n", n, m, delannoy(n, m));
    return EXIT_SUCCESS;
}