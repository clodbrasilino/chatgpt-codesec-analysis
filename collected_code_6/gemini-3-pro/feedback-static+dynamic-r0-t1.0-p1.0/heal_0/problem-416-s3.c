#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100000

long long dp[MAX_SIZE];

long long max(long long a, long long b) {
    return (a > b) ? a : b;
}

long long findMaxSum(long long n) {
    if (n < 3) {
        return n;
    }

    if (n < MAX_SIZE) {
        if (dp[n] != -1) {
            return dp[n];
        }
    }

    long long sum = max(n, findMaxSum(n / 2) + findMaxSum(n / 3) + findMaxSum(n / 4));

    if (n < MAX_SIZE) {
        dp[n] = sum;
    }

    return sum;
}

int main(void) {
    long long n;

    for (int i = 0; i < MAX_SIZE; i++) {
        dp[i] = -1;
    }

    if (scanf("%lld", &n) != 1) {
        return EXIT_FAILURE;
    }

    if (n < 0) {
        return EXIT_FAILURE;
    }

    printf("%lld\n", findMaxSum(n));

    return EXIT_SUCCESS;
}