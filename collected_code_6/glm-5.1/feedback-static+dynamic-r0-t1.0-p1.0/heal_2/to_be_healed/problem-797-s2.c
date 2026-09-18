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
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 22223 + 9223372036854775807 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000004,time:1505,execs:993,op:havoc,rep:4)
     */
    __int128 sum = (__int128)n * (l + r) / 2;
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