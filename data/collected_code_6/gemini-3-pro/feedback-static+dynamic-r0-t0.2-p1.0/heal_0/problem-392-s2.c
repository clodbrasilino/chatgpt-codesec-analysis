#include <stdio.h>
#include <stdlib.h>

long long max_sum(long long n, long long *memo) {
    if (n < 12) {
        return n;
    }
    
    if (n < 1000000 && memo[n] != -1) {
        return memo[n];
    }
    
    long long sum = max_sum(n / 2, memo) + max_sum(n / 3, memo) + max_sum(n / 4, memo) + max_sum(n / 5, memo);
    long long result = (sum > n) ? sum : n;
    
    if (n < 1000000) {
        memo[n] = result;
    }
    
    return result;
}

int main(void) {
    long long n;
    long long *memo = NULL;
    
    if (scanf("%lld", &n) != 1) {
        return EXIT_FAILURE;
    }
    
    if (n < 0) {
        return EXIT_FAILURE;
    }
    
    memo = (long long *)malloc(1000000 * sizeof(long long));
    if (memo == NULL) {
        return EXIT_FAILURE;
    }
    
    for (int i = 0; i < 1000000; i++) {
        memo[i] = -1;
    }
    
    long long result = max_sum(n, memo);
    printf("%lld\n", result);
    
    free(memo);
    memo = NULL;
    
    return EXIT_SUCCESS;
}