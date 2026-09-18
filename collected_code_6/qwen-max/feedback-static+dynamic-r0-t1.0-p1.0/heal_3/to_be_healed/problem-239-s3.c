#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int64_t count_sequences(int n, int m) {
    if (n == 0 || m == 0) return 1;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 110379845 * -1342157943 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000002,time:8,execs:15,op:(null),pos:0)
     */
    int64_t *dp = (int64_t *)malloc((n + 1) * (m + 1) * sizeof(int64_t));
    for (int j = 1; j <= m; ++j) dp[j] = 1;
    for (int i = 2; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            dp[(i-1)*(m+1) + j] = 0;
            for (int k = 1; k * 2 <= j; ++k) {
                dp[(i-1)*(m+1) + j] += dp[(i-2)*(m+1) + k];
            }
        }
    }
    int64_t result = 0;
    for (int j = 1; j <= m; ++j) {
        result += dp[(n-1)*(m+1) + j];
    }
    free(dp);
    return result;
}

int main() {
    int n, m;
    printf("Enter the length of the sequence (n): ");
    scanf("%d", &n);
    printf("Enter the maximum value in the sequence (m): ");
    scanf("%d", &m);
    int64_t result = count_sequences(n, m);
    /* Possible weaknesses found:
     *  %lld in format string (no. 1) requires 'long long' but the argument type is 'signed long'. [invalidPrintfArgType_sint]
     */
    printf("Number of sequences: %lld\n", result);
    return 0;
}