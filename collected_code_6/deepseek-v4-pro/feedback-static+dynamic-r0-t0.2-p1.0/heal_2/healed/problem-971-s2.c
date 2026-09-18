#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int maxSegments(int n, int a, int b, int c) {
    if (n < 0) {
        return -1;
    }
    
    if (a <= 0 || b <= 0 || c <= 0) {
        return -1;
    }
    
    int *dp = malloc((n + 1) * sizeof(int));
    if (dp == NULL) {
        return -1;
    }
    
    for (int i = 0; i <= n; i++) {
        dp[i] = INT_MIN;
    }
    
    dp[0] = 0;
    
    for (int i = 1; i <= n; i++) {
        if (i >= a && dp[i - a] != INT_MIN) {
            dp[i] = dp[i - a] + 1;
        }
        if (i >= b && dp[i - b] != INT_MIN) {
            int val = dp[i - b] + 1;
            if (val > dp[i]) {
                dp[i] = val;
            }
        }
        if (i >= c && dp[i - c] != INT_MIN) {
            int val = dp[i - c] + 1;
            if (val > dp[i]) {
                dp[i] = val;
            }
        }
    }
    
    int result = dp[n] == INT_MIN ? -1 : dp[n];
    free(dp);
    return result;
}

int main(void) {
    int n, a, b, c;
    
    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    printf("Enter a, b, c: ");
    if (scanf("%d %d %d", &a, &b, &c) != 3) {
        printf("Invalid input\n");
        return 1;
    }
    
    if (n < 0) {
        printf("Cannot form segments\n");
        return 0;
    }
    
    int result = maxSegments(n, a, b, c);
    
    if (result == -1) {
        printf("Cannot form segments\n");
    } else {
        printf("Maximum segments: %d\n", result);
    }
    
    return 0;
}