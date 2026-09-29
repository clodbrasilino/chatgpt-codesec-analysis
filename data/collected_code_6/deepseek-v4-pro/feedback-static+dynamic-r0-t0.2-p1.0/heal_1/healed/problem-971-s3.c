#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

int maxSegments(int n, int a, int b, int c) {
    int *dp;
    int i;
    int result;
    
    if (n < 0) {
        return -1;
    }
    
    if (n > 1000000) {
        return -1;
    }
    
    dp = (int *)malloc((n + 1) * sizeof(int));
    if (dp == NULL) {
        return -1;
    }
    
    dp[0] = 0;
    
    for (i = 1; i <= n; i++) {
        dp[i] = -1;
    }
    
    for (i = 1; i <= n; i++) {
        if (i >= a && dp[i - a] != -1) {
            dp[i] = dp[i - a] + 1;
        }
        if (i >= b && dp[i - b] != -1) {
            if (dp[i - b] + 1 > dp[i]) {
                dp[i] = dp[i - b] + 1;
            }
        }
        if (i >= c && dp[i - c] != -1) {
            if (dp[i - c] + 1 > dp[i]) {
                dp[i] = dp[i - c] + 1;
            }
        }
    }
    
    result = dp[n];
    free(dp);
    
    return result;
}

int main(void) {
    int n, a, b, c;
    
    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        return 1;
    }
    
    printf("Enter a, b, c: ");
    if (scanf("%d %d %d", &a, &b, &c) != 3) {
        return 1;
    }
    
    if (n < 0 || a <= 0 || b <= 0 || c <= 0) {
        return 1;
    }
    
    int result = maxSegments(n, a, b, c);
    
    if (result == -1) {
        printf("Cannot form any segments\n");
    } else {
        printf("Maximum segments: %d\n", result);
    }
    
    return 0;
}