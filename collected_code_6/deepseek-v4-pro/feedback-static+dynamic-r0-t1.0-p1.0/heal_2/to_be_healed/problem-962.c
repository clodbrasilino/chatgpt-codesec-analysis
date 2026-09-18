#include <stdio.h>

long long sum_even_natural_range(long long l, long long r) {
    if (l < 1) {
        l = 1;
    }
    if (r < 1) {
        r = 1;
    }
    if (l > r) {
        return 0;
    }
    if (l % 2 != 0) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 9223372036854775807 + 1 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000004,time:26530,execs:15982,op:havoc,rep:2)
         */
        l++;
    }
    if (r % 2 != 0) {
        r--;
    }
    if (l > r) {
        return 0;
    }
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 9223372036854775806 - -9223372036854775808 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000004,time:26530,execs:15982,op:havoc,rep:2)
     */
    long long n = (r - l) / 2 + 1;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 4 + 9223372036854775806 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000004,time:3024,execs:1923,op:havoc,rep:1)
     * UBSan: signed integer overflow: 4611686018427387902 * -9223372036854775806 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000004,time:3024,execs:1923,op:havoc,rep:1)
     * UBSan: signed integer overflow: 166666666666665 * 333333333333336 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000004,time:971,execs:613,op:havoc,rep:4)
     */
    return n * (l + r) / 2;
}

int main(void) {
    long long l, r;
    if (scanf("%lld %lld", &l, &r) != 2) {
        return 1;
    }
    printf("%lld\n", sum_even_natural_range(l, r));
    return 0;
}