#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

static int maxSegments(int n, int a, int b, int c, int *memo) {
    if (n < 0) return INT_MIN;
    if (n == 0) return 0;
    if (memo[n] != -2) return memo[n];
    
    int max = INT_MIN;
    int val;
    
    if (n >= a) {
        val = maxSegments(n - a, a, b, c, memo);
        if (val != INT_MIN && val + 1 > max) max = val + 1;
    } else {
        val = maxSegments(n - a, a, b, c, memo);
        if (val != INT_MIN && val + 1 > max) max = val + 1;
    }
    
    if (n >= b && b != a) {
        val = maxSegments(n - b, a, b, c, memo);
        if (val != INT_MIN && val + 1 > max) max = val + 1;
    } else if (b != a) {
        val = maxSegments(n - b, a, b, c, memo);
        if (val != INT_MIN && val + 1 > max) max = val + 1;
    }
    
    if (n >= c && c != a && c != b) {
        val = maxSegments(n - c, a, b, c, memo);
        if (val != INT_MIN && val + 1 > max) max = val + 1;
    } else if (c != a && c != b) {
        val = maxSegments(n - c, a, b, c, memo);
        if (val != INT_MIN && val + 1 > max) max = val + 1;
    }
    
    memo[n] = max;
    return max;
}

static int maxSegmentsIterative(int n, int a, int b, int c) {
    int *dp = malloc((n + 1) * sizeof(int));
    if (dp == NULL) return INT_MIN;
    
    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        dp[i] = INT_MIN;
    }
    
    for (int i = 1; i <= n; i++) {
        if (i >= a && dp[i - a] != INT_MIN) {
            if (dp[i - a] + 1 > dp[i]) dp[i] = dp[i - a] + 1;
        }
        if (i >= b && dp[i - b] != INT_MIN) {
            if (dp[i - b] + 1 > dp[i]) dp[i] = dp[i - b] + 1;
        }
        if (i >= c && dp[i - c] != INT_MIN) {
            if (dp[i - c] + 1 > dp[i]) dp[i] = dp[i - c] + 1;
        }
    }
    
    int result = dp[n];
    free(dp);
    return result;
}

int main(void) {
    int n, a, b, c;
    
    printf("Enter n: ");
    if (scanf("%d", &n) != 1) return 1;
    
    if (n < 0) {
        printf("Cannot form segments\n");
        return 0;
    }
    
    printf("Enter a, b, c: ");
    if (scanf("%d %d %d", &a, &b, &c) != 3) return 1;
    
    if (a <= 0 || b <= 0 || c <= 0) {
        printf("Segment lengths must be positive\n");
        return 1;
    }
    
    if (n > 1000000) {
        printf("Input too large\n");
        return 1;
    }
    
    int result;
    
    if (n > 100000) {
        result = maxSegmentsIterative(n, a, b, c);
    } else {
        int *memo = malloc((n + 1) * sizeof(int));
        if (memo == NULL) {
            printf("Memory allocation failed\n");
            return 1;
        }
        
        for (int i = 0; i <= n; i++) {
            memo[i] = -2;
        }
        
        result = maxSegments(n, a, b, c, memo);
        free(memo);
    }
    
    if (result <= 0 || result == INT_MIN) {
        printf("Cannot form segments\n");
    } else {
        printf("Maximum segments: %d\n", result);
    }
    
    return 0;
}