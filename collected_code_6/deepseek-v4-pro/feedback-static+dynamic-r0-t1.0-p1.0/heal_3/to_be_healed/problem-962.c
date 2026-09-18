#include <stdio.h>
#include <limits.h>

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
        if (l == LLONG_MAX) {
            return 0;
        }
        l++;
    }
    if (r % 2 != 0) {
        r--;
    }
    /* Possible weaknesses found:
     *  Assuming that condition 'l>r' is not redundant
     */
    if (l > r) {
        return 0;
    }
    /* Possible weaknesses found:
     *  Condition 'r-l<0' is always false [knownConditionTrueFalse]
     *  Condition 'r-l<0' is always false
     */
    if (r - l < 0) {
        return 0;
    }
    long long n = (r - l) / 2 + 1;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 22 + 9223372036854775806 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000004,time:4887,execs:3145,op:havoc,rep:2)
     */
    if (n > LLONG_MAX / (l + r)) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 22 + 9223372036854775806 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000004,time:4887,execs:3145,op:havoc,rep:2)
         */
        if (l + r == 0) {
            return 0;
        }
        if (n % 2 == 0) {
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 833333333333333250 * 3333333333333333666 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000002,time:681,execs:463,op:havoc,rep:2)
             */
            return (n / 2) * (l + r);
        } else {
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: -4611686018427387894 * 4611686018427387893 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000004,time:4887,execs:3145,op:havoc,rep:2)
             * UBSan: signed integer overflow: 111111111112 * 111111111111 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000004,time:3826,execs:2464,op:havoc,rep:5)
             * UBSan: signed integer overflow: 22 + 9223372036854775806 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000004,time:4887,execs:3145,op:havoc,rep:2)
             */
            return ((l + r) / 2) * n;
        }
    }
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