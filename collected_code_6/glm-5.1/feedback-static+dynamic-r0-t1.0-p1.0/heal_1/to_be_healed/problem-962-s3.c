#include <stdio.h>

long long sum_even_natural_numbers(long long l, long long r) {
    if (l > r) {
        return 0;
    }
    if (l <= 0) {
        l = 1;
    }
    if (r <= 0) {
        return 0;
    }
    if (l % 2 != 0) {
        l++;
    }
    if (l > r) {
        return 0;
    }
    long long n = ((r - l) / 2) + 1;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 4611686018427371237 * -9223372036854742476 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000002,time:2309,execs:1498,op:havoc,rep:3)
     * UBSan: signed integer overflow: 49999999999999 * 100000000000000 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000001,time:16272,execs:10203,op:havoc,rep:13)
     * UBSan: signed integer overflow: 33334 + 9223372036854775807 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000002,time:2309,execs:1498,op:havoc,rep:3)
     * UBSan: signed integer overflow: 5557500000 * 11115222222 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000005,time:9458,execs:6125,op:havoc,rep:4)
     */
    return n * (l + r - ((r % 2 != 0) ? 1 : 0)) / 2;
}

int main() {
    long long l, r;
    if (scanf("%lld %lld", &l, &r) != 2) {
        return 1;
    }
    long long result = sum_even_natural_numbers(l, r);
    printf("%lld\n", result);
    return 0;
}