#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

long long f(int n, long long *memo) {
    if (n < 2) return n;

    if (memo[n] != -1) return memo[n];

    long long a = f(n / 2, memo);
    long long b = f(n / 3, memo);
    long long c = f(n / 4, memo);
    long long d = f(n / 5, memo);

    long long val = max(n, a + b + c + d);
    memo[n] = val;
    return val;
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);

    long long *memo = (long long *)calloc(n + 1, sizeof(long long));
    for (int i = 0; i <= n; ++i) {
        memo[i] = -1;
    }

    long long result = f(n, memo);
    printf("Maximum sum possible: %lld\n", result);

    free(memo);
    return 0;
}