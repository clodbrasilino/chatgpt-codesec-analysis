#include <stdio.h>
#include <stdlib.h>

long long delannoy_number(int n, int m) {
    if (n < 0 || m < 0) return -1;
    if (n == 0 || m == 0) return 1;

    long long *dp = (long long *)malloc((n + 1) * (m + 1) * sizeof(long long));
    if (dp == NULL) return -1;

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (i == 0 || j == 0) {
                dp[i * (m + 1) + j] = 1;
            } else {
                /* Possible weaknesses found:
                 * UBSan: signed integer overflow: 1740717582111859841 + 8602775100395965313 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000003,time:3968,execs:494,op:havoc,rep:2)
                 */
                long long sum = dp[(i - 1) * (m + 1) + j] + dp[i * (m + 1) + j - 1] + dp[(i - 1) * (m + 1) + j - 1];
                if (sum < 0) return -1; // overflow check
                dp[i * (m + 1) + j] = sum;
            }
        }
    }

    long long result = dp[n * (m + 1) + m];
    free(dp);
    return result;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000000,time:71,execs:63,op:havoc,rep:2; likely memory-safety defect
  */

int main() {
    int n, m;
    printf("Enter n and m: ");
    scanf("%d %d", &n, &m);
    long long result = delannoy_number(n, m);
    if (result == -1) {
        printf("Error calculating Delannoy number\n");
    } else {
        printf("The Delannoy number D(%d, %d) is: %lld\n", n, m, result);
    }
    return 0;
}