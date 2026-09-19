#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>

long long count_binary_sequences(int n) {
    if (n <= 0) {
        return 0;
    }
    
    long long *dp = (long long *)calloc(n + 1, sizeof(long long));
    if (dp == NULL) {
        return -1;
    }
    
    dp[0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = i; j >= 1; j--) {
            if (dp[j] > LLONG_MAX - dp[j - 1]) {
                free(dp);
                return -1;
            }
            dp[j] += dp[j - 1];
        }
    }
    
    long long total = 0;
    for (int k = 0; k <= n; k++) {
        if (dp[k] > 0 && dp[k] > LLONG_MAX / dp[k]) {
            free(dp);
            return -1;
        }
        long long square = dp[k] * dp[k];
        if (total > LLONG_MAX - square) {
            free(dp);
            return -1;
        }
        total += square;
    }
    
    free(dp);
    return total;
}

int main(void) {
    int n;
    long long result;
    
    if (scanf("%d", &n) != 1) {
        return 1;
    }
    
    if (n <= 0) {
        return 1;
    }
    
    result = count_binary_sequences(n);
    if (result == -1) {
        return 1;
    }
    
    printf("%.1f\n", (double)result);
    return 0;
}