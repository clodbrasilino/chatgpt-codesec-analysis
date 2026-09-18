#include <stdio.h>
#include <stdint.h>

long long sum_odd_natural_numbers(long long l, long long r) {
    if (l > r) {
        return 0;
    }
    if (l <= 0) {
        l = 1;
    }
    if (r <= 0) {
        return 0;
    }
    if (l % 2 == 0) {
        l++;
    }
    if (r % 2 == 0) {
        r--;
    }
    if (l > r) {
        return 0;
    }
    long long n = ((r - l) / 2) + 1;
    __int128 half_l = l / 2;
    __int128 sum = n * (half_l + r);
    if (sum > 9223372036854775807LL) {
        return 9223372036854775807LL;
    }
    return (long long)sum;
}

int main(void) {
    long long l, r;
    if (scanf("%lld %lld", &l, &r) != 2) {
        return 1;
    }
    long long result = sum_odd_natural_numbers(l, r);
    printf("%lld\n", result);
    return 0;
}