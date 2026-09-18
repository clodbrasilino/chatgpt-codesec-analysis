#include <stdio.h>
#include <limits.h>

long long find_largest_k(long long x, long long y) {
    if (x <= 0 || y < 0 || y >= x) {
        return -1;
    }
    
    long long remainder = LLONG_MAX % x;
    long long largest_multiple = LLONG_MAX - remainder;
    
    if (remainder >= y) {
        return largest_multiple + y;
    } else {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 9223372036854775807 + 1 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000003,time:587,execs:261,op:havoc,rep:1)
         * UBSan: signed integer overflow: -9223372036854775808 - 9223372036854775807 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000003,time:587,execs:261,op:havoc,rep:1)
         */
        return largest_multiple + y - x;
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