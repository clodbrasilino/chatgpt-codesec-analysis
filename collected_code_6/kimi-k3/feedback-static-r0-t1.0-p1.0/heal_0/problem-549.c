#include <stdio.h>

long long sum_fifth_power_odd(int n) {
    long long sum = 0;
    int i;
    for (i = 0; i < n; i++) {
        long long odd = 2LL * i + 1;
        long long power = odd * odd * odd * odd * odd;
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