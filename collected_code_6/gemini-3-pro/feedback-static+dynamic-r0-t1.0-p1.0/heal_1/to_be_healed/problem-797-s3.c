#include <stdio.h>
#include <stdlib.h>

long long sum_of_odds(long long l, long long r) {
    if (l > r) {
        return 0;
    }
    if (l < 0) {
        l = 1;
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
    long long n = (r - l) / 2 + 1;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 23 + 9223372036854775807 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:1015,execs:520,op:havoc,rep:2)
     * UBSan: signed integer overflow: 1111111111110 * 2222222222224 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000006,time:9947,execs:4696,op:havoc,rep:1)
     * UBSan: signed integer overflow: 4611686018427387893 * -9223372036854775786 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:1015,execs:520,op:havoc,rep:2)
     * UBSan: signed integer overflow: 11111111111112 * 22222222222228 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:486,execs:260,op:havoc,rep:1)
     */
    long long sum = n * (l + r) / 2;
    return sum;
}

int main() {
    long long l, r;
    if (scanf("%lld %lld", &l, &r) != 2) {
        return EXIT_FAILURE;
    }
    long long result = sum_of_odds(l, r);
    printf("%lld\n", result);
    return EXIT_SUCCESS;
}