#include <stdio.h>
#include <stdlib.h>

long long *memo;

long long f(long long n) {
    if (n <= 0) {
        return 0;
    }
    if (n < 1000000) {
        if (memo[n] != -1) {
            return memo[n];
        }
    }
    long long sum = f(n / 2) + f(n / 3) + f(n / 4) + f(n / 5);
    long long result = sum > n ? sum : n;
    if (n < 1000000) {
        memo[n] = result;
    }
    return result;
}

int main(void) {
    long long n;
    memo = (long long *)malloc(1000000 * sizeof(long long));
    if (memo == NULL) {
        return 1;
    }
    for (long long i = 0; i < 1000000; i++) {
        memo[i] = -1;
    }
    if (scanf("%lld", &n) == 1) {
        printf("%lld\n", f(n));
    }
    free(memo);
    memo = NULL;
    return 0;
}