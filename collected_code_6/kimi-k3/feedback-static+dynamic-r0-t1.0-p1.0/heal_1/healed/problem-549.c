#include <stdio.h>
#include <limits.h>

long long sum_fifth_power_odd(int n) {
    long long sum = 0;
    int i;
    for (i = 0; i < n; i++) {
        long long odd = 2LL * i + 1;
        if (odd > LLONG_MAX / odd) break;
        long long p2 = odd * odd;
        if (p2 > LLONG_MAX / odd) break;
        long long p3 = p2 * odd;
        if (p3 > LLONG_MAX / odd) break;
        long long p4 = p3 * odd;
        if (p4 > LLONG_MAX / odd) break;
        long long power = p4 * odd;
        if (sum > LLONG_MAX - power) break;
        sum += power;
    }
    return sum;
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) {
        return 1;
    }
    if (n < 0) {
        return 1;
    }
    printf("%lld\n", sum_fifth_power_odd(n));
    return 0;
}