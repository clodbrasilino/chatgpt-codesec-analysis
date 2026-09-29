#include <stdio.h>
#include <stdlib.h>

long long *memo;

long long max(long long a, long long b) {
    return a > b ? a : b;
}

long long f(long long n) {
    if (n == 0) return 0;
    if (n < 12) return n;
    if (memo[n] != -1) return memo[n];
    memo[n] = max(n, f(n / 2) + f(n / 3) + f(n / 4) + f(n / 5));
    return memo[n];
}

int main() {
    long long n;
    printf("Enter n: ");
    if (scanf("%lld", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    if (n < 0) {
        fprintf(stderr, "n must be non-negative\n");
        return 1;
    }
    memo = (long long *)malloc((n + 1) * sizeof(long long));
    if (memo == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    for (long long i = 0; i <= n; i++) {
        memo[i] = -1;
    }
    printf("%lld\n", f(n));
    free(memo);
    return 0;
}