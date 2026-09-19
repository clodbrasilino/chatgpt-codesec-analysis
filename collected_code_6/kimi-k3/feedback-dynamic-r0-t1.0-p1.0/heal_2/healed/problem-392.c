#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

long long max_sum(long long n, long long *memo, long long size) {
    if (n == 0) {
        return 0;
    }
    if (n < size && memo[n] != -1) {
        return memo[n];
    }
    long long sum = 0;
    long long sub;
    
    sub = max_sum(n / 2, memo, size);
    if (sub > LLONG_MAX - sum) {
        sum = LLONG_MAX;
    } else {
        sum += sub;
    }
    
    sub = max_sum(n / 3, memo, size);
    if (sub > LLONG_MAX - sum) {
        sum = LLONG_MAX;
    } else {
        sum += sub;
    }
    
    sub = max_sum(n / 4, memo, size);
    if (sub > LLONG_MAX - sum) {
        sum = LLONG_MAX;
    } else {
        sum += sub;
    }
    
    sub = max_sum(n / 5, memo, size);
    if (sub > LLONG_MAX - sum) {
        sum = LLONG_MAX;
    } else {
        sum += sub;
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
    if (size <= 0 || (uintmax_t)size > (uintmax_t)SIZE_MAX / sizeof(long long)) {
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