#include <stdio.h>
#include <stdlib.h>

int domino_tilings_3xn(int n) {
    if (n < 0) return 0;
    if (n % 2 != 0) return 0;
    
    int *dp = (int*)malloc((n + 1) * sizeof(int));
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
                /* Possible weaknesses found:
                 * UBSan: signed integer overflow: -888806596 - 1399659044 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000000,time:893,execs:445,op:havoc,rep:15)
                 * UBSan: signed integer overflow: 4 * 1525870529 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000000,time:893,execs:445,op:havoc,rep:15)
                 */
                dp[i] = 4 * dp[i - 2] - dp[i - 4];
            } else {
                dp[i] = 4 * dp[i - 2];
            }
        }
    }
    
    int result = dp[n];
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
    
    int ways = domino_tilings_3xn(n);
    printf("Number of ways to tile 3x%d board: %d\n", n, ways);
    
    return 0;
}