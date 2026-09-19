#include <stdio.h>
#include <limits.h>

long long cubeSumOdd(int n) {
    long long sum = 0;
    if (n <= 0) {
        return 0;
    }
    for (int i = 1; i <= n; i++) {
        long long odd = 2LL * i - 1;
        if (odd > LLONG_MAX / odd / odd) {
            return -1;
        }
        long long cube = odd * odd * odd;
        if (sum > LLONG_MAX - cube) {
            return -1;
        }
        sum += cube;
    }
    return sum;
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) {
        return 1;
    }
    printf("%lld\n", cubeSumOdd(n));
    return 0;
}