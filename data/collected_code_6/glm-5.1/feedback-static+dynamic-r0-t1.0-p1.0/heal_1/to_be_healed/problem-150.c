#include <stdio.h>
#include <stdbool.h>

bool isInSequence(long long a, long long d, long long num) {
    if (d == 0) {
        return a == num;
    }
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: -9223372036854775808 - 3 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000005,time:2911,execs:1604,op:havoc,rep:3)
     */
    if ((num - a) % d != 0) {
        return false;
    }
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: -9223372036854775808 - 3 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000005,time:2911,execs:1604,op:havoc,rep:3)
     */
    long long n = (num - a) / d;
    return n >= 0;
}

int main() {
    long long a, d, num;
    if (scanf("%lld %lld %lld", &a, &d, &num) != 3) {
        return 1;
    }
    if (isInSequence(a, d, num)) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }
    return 0;
}