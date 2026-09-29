#include <stdio.h>
#include <stdlib.h>

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
            dp[j] += dp[j - 1];
        }
    }
    
    long long total = 0;
    for (int k = 0; k <= n; k++) {
        total += dp[k] * dp[k];
    }
    
    free(dp);
    return total;
}

int main(void) {
    int n;
    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (n <= 0) {
        fprintf(stderr, "n must be positive\n");
        return 1;
    }
    
    long long result = count_binary_sequences(n);
    if (result == -1) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    printf("%lld\n", result);
    return 0;
}