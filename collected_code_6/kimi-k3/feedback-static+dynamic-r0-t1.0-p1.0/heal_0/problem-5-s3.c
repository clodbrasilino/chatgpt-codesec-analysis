#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

long long count_domino_tilings(int n) {
    if (n < 0 || n % 2 != 0) {
        return 0;
    }
    
    if (n == 0) {
        return 1;
    }
    
    long long *dp = (long long *)calloc((size_t)n + 1, sizeof(long long));
    if (dp == NULL) {
        return -1;
    }
    
    dp[0] = 1;
    dp[2] = 3;
    
    for (int i = 4; i <= n; i += 2) {
        dp[i] = 3 * dp[i - 2];
        for (int j = 4; j <= i; j += 2) {
            dp[i] += 2 * dp[i - j];
        }
    }
    
    long long result = dp[n];
    free(dp);
    dp = NULL;
    
    return result;
}

int main(void) {
    int n;
    char buffer[256];
    char *endptr;
    long val;
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    errno = 0;
    val = strtol(buffer, &endptr, 10);
    
    if (errno == ERANGE || val > INT_MAX || val < 0 || endptr == buffer) {
        fprintf(stderr, "Invalid input: must be a non-negative integer\n");
        return EXIT_FAILURE;
    }
    
    n = (int)val;
    
    if (n % 2 != 0) {
        printf("0\n");
        return EXIT_SUCCESS;
    }
    
    long long result = count_domino_tilings(n);
    
    if (result < 0) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    printf("%lld\n", result);
    
    return EXIT_SUCCESS;
}