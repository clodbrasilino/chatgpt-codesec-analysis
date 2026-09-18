#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long max_sum(long long n, long long *memo, long long size) {
    if (n < size && memo[n] != -1) {
        return memo[n];
    }
    if (n == 0) {
        return 0;
    }
    
    long long sum = 0;
    long long parts[4] = {n / 2, n / 3, n / 4, n / 5};
    
    for (int i = 0; i < 4; i++) {
        long long val = max_sum(parts[i], memo, size);
        if (val > LLONG_MAX - sum) {
            sum = LLONG_MAX;
            break;
        }
        sum += val;
    }
    
    long long result = (sum > n) ? sum : n;
    if (n < size) {
        memo[n] = result;
    }
    return result;
}

int main() {
    long long n;
    if (scanf("%lld", &n) != 1 || n < 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (n == LLONG_MAX) {
        fprintf(stderr, "Input too large\n");
        return EXIT_FAILURE;
    }
    
    long long size = n + 1;
    
    if ((size_t)size > SIZE_MAX / sizeof(long long)) {
        fprintf(stderr, "Input too large\n");
        return EXIT_FAILURE;
    }
    
    long long *memo = malloc((size_t)size * sizeof(long long));
    if (memo == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    for (long long i = 0; i < size; i++) {
        memo[i] = -1;
    }
    
    printf("%lld\n", max_sum(n, memo, size));
    free(memo);
    return EXIT_SUCCESS;
}