#include <stdio.h>
#include <limits.h>

long long cube_sum_odd(int n) {
    if (n <= 0) {
        return 0;
    }
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        long long odd_num = 2LL * i + 1;
        long long cubed = odd_num * odd_num * odd_num;
        if (cubed / odd_num != odd_num * odd_num) {
            return LLONG_MAX;
        }
        if (sum > LLONG_MAX - cubed) {
            return LLONG_MAX;
        }
        sum += cubed;
    }
    return sum;
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1 || n < 0) {
        return 1;
    }
    long long result = cube_sum_odd(n);
    if (result == LLONG_MAX) {
        return 1;
    }
    printf("%lld\n", result);
    return 0;
}