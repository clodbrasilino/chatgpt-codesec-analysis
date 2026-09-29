#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000000

long long memo[MAX_N];

long long f(long long n) {
    if (n < 0) {
        return 0;
    }
    if (n == 0) {
        return 0;
    }
    if (n < MAX_N) {
        if (memo[n] != 0) {
            return memo[n];
        }
    }
    long long sum = f(n / 2) + f(n / 3) + f(n / 4) + f(n / 5);
    long long result = sum > n ? sum : n;
    if (n < MAX_N) {
        memo[n] = result;
    }
    return result;
}

int main(void) {
    long long n;
    for (long long i = 0; i < MAX_N; i++) {
        memo[i] = 0;
    }
    while (scanf("%lld", &n) == 1) {
        printf("%lld\n", f(n));
    }
    return 0;
}