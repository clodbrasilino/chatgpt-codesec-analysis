#include <stdio.h>
#include <stdlib.h>

long long countSequences(int n, int m) {
    if (n < 0 || m < 0) {
        return 0;
    }
    long long *dp = (long long *)malloc((n + 1) * (m + 1) * sizeof(long long));
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            if (i == 0 || j == 0) {
                dp[i * (m + 1) + j] = 0;
            } else if (i == 1) {
                dp[i * (m + 1) + j] = 1;
            } else {
                dp[i * (m + 1) + j] = (dp[(i - 1) * (m + 1) + j] + dp[(i - 1) * (m + 1) + j - 1]) % 1000000007;
            }
        }
    }
    long long result = dp[n * (m + 1) + m];
    free(dp);
    return result;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:15,execs:15,op:(null),pos:0; likely memory-safety defect
  */

int main() {
    int n, m;
    printf("Enter the length of the sequence and the maximum value: ");
    scanf("%d %d", &n, &m);
    if (n >= 0 && m >= 0) {
        long long result = countSequences(n, m);
        printf("Number of sequences: %lld\n", result);
    } else {
        printf("Invalid input. Please enter non-negative integers.\n");
    }
    return 0;
}