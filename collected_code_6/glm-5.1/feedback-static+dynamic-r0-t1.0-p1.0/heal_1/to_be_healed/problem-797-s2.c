#include <stdio.h>

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
     * UBSan: signed integer overflow: 1 + 9223372036854775807 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000005,time:6667,execs:4040,op:havoc,rep:3)
     * UBSan: signed integer overflow: 4611686018427387904 * -9223372036854775808 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000005,time:6667,execs:4040,op:havoc,rep:3)
     * UBSan: signed integer overflow: 11111111110 * 22222222224 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000004,time:3212,execs:1872,op:havoc,rep:4)
     */
    return n * (l + r) / 2;
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