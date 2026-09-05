#include <stdio.h>
#include <stdlib.h>

long long count_binary_sequences(int n) {
    if (n <= 0) {
        return 0;
    }
    
    int max_sum = n;
    long long *dp = (long long *)calloc(max_sum + 1, sizeof(long long));
    if (dp == NULL) {
        exit(EXIT_FAILURE);
    }
    
    dp[0] = 1;
    
    for (int i = 0; i < n; i++) {
        for (int j = max_sum; j > 0; j--) {
            dp[j] += dp[j - 1];
        }
    }
    
    long long total_count = 0;
    for (int i = 0; i <= max_sum; i++) {
        total_count += dp[i] * dp[i];
    }
    
    free(dp);
    return total_count;
}

int main() {
    int n = 5;
    long long result = count_binary_sequences(n);
    printf("%lld\n", result);
    return 0;
}