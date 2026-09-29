#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

long f(long n, long *memo) {
    if (n < 0) return 0;
    if (memo[n] != -1) return memo[n];
    long result = max(n, f(n/2, memo) + f(n/3, memo) + f(n/4, memo) + f(n/5, memo));
    memo[n] = result;
    return result;
}

int main() {
    long n;
    printf("Enter a number: ");
    if (scanf("%ld", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    long *memo = (long *)calloc(n+1, sizeof(long));
    if (memo == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    for (long i = 0; i <= n; ++i) {
        memo[i] = -1;
    }

    long result = f(n, memo);
    printf("Maximum sum: %ld\n", result);

    free(memo);
    return 0;
}