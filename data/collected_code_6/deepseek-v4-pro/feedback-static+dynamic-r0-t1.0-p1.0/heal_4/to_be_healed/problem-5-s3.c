#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

int64_t domino_tilings_3xn(int n) {
    if (n < 0) return 0;
    if (n % 2 != 0) return 0;
    
    if (n > 60) return -1;
    
    int64_t *dp = (int64_t*)malloc((n + 1) * sizeof(int64_t));
    if (dp == NULL) return 0;
    
    dp[0] = 1;
    if (n >= 1) {
        dp[1] = 0;
    }
    
    for (int i = 2; i <= n; i++) {
        if (i % 2 != 0) {
            dp[i] = 0;
        } else {
            if (i >= 4) {
                int64_t term1;
                int64_t term2;
                
                if (dp[i - 2] > INT64_MAX / 4) {
                    free(dp);
                    return -1;
                }
                term1 = 4 * dp[i - 2];
                
                /* Possible weaknesses found:
                 * UBSan: signed integer overflow: 9223372036854775807 + 1 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:504,execs:314,op:havoc,rep:1)
                 */
                if (term1 < INT64_MIN + dp[i - 4] || term1 > INT64_MAX + dp[i - 4]) {
                    free(dp);
                    return -1;
                }
                
                term2 = term1 - dp[i - 4];
                dp[i] = term2;
            } else {
                if (dp[i - 2] > INT64_MAX / 4) {
                    free(dp);
                    return -1;
                }
                dp[i] = 4 * dp[i - 2];
            }
        }
    }
    
    int64_t result = dp[n];
    free(dp);
    return result;
}

int main(void) {
    int n;
    printf("Enter board width n: ");
    if (scanf("%d", &n) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    
    int64_t ways = domino_tilings_3xn(n);
    if (ways == -1) {
        printf("Overflow detected: n is too large to compute safely\n");
        return 1;
    }
    
    printf("Number of ways to tile 3x%d board: %" PRId64 "\n", n, ways);
    
    return 0;
}