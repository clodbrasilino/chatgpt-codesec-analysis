#include <stdio.h>
#include <limits.h>

long long find_largest_k(long long x, long long y) {
    if (x <= 0 || y < 0 || y >= x) {
        return -1;
    }
    
    if (LLONG_MAX % x >= y) {
        return LLONG_MAX - (LLONG_MAX % x) + y;
    } else {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: -9223372036854775807 - 17 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:472,execs:217,op:havoc,rep:5)
         * UBSan: signed integer overflow: 9223372036854775799 + 10 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:472,execs:217,op:havoc,rep:5)
         */
        return LLONG_MAX - (LLONG_MAX % x) + y - x;
    }
}

int main(void) {
    long long x, y;
    
    if (scanf("%lld %lld", &x, &y) != 2) {
        return 1;
    }
    
    long long result = find_largest_k(x, y);
    printf("%lld\n", result);
    
    return 0;
}