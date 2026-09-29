#include <stdio.h>
#include <stdlib.h>

long long domino_tilings_3xn(int n) {
    if (n < 0) return 0;
    if (n % 2 != 0) return 0;
    
    long long *dp = (long long*)malloc((n + 1) * sizeof(long long));
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
                dp[i] = 4 * dp[i - 2] - dp[i - 4];
            } else {
                dp[i] = 4 * dp[i - 2];
            }
        }
    }
    
    long long result = dp[n];
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
    
    long long ways = domino_tilings_3xn(n);
    printf("Number of ways to tile 3x%d board: %lld\n", n, ways);
    
    return 0;
}