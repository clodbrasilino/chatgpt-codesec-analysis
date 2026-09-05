#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000000

long long memo[MAX_N];

long long f(long long n) {
    if (n < 2) {
        return n;
    }
    if (n < MAX_N) {
        if (memo[n] != 0) {
            return memo[n];
        }
        memo[n] = (f(n / 2) + f(n / 3) + f(n / 4) + f(n / 5));
        if (memo[n] < n) {
            memo[n] = n;
        }
        return memo[n];
    }
    long long sum = (f(n / 2) + f(n / 3) + f(n / 4) + f(n / 5));
    if (sum < n) {
        return n;
    }
    return sum;
}

int main(void) {
    long long n;
    if (scanf("%lld", &n) == 1) {
        printf("%lld\n", f(n));
    }
    return 0;
}