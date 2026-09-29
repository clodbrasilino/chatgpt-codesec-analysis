#include <stdio.h>

long long count_rectangles(long long r) {
    if (r <= 0) {
        return 0;
    }
    
    long long count = 0;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 40000000000 * 10000000000 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000003,time:3209,execs:1618,op:havoc,rep:2)
     * UBSan: signed integer overflow: 4 * 9223372036854775807 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000003,time:4890,execs:2456,op:havoc,rep:2)
     * UBSan: signed integer overflow: -4 * 9223372036854775807 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000003,time:4890,execs:2456,op:havoc,rep:2)
     */
    long long limit = 4LL * r * r;
    long long h = 1;
    
    while (h * h <= limit) {
        h++;
    }
    h--;
    
    for (long long w = 1; w * w < limit; w++) {
        while (h > 0 && (w * w + h * h) > limit) {
            h--;
        }
        count += h;
    }
    
    return count;
}

int main(void) {
    long long r = 0;
    
    if (scanf("%lld", &r) != 1) {
        return 1;
    }
    
    if (r < 0) {
        return 1;
    }
    
    long long result = count_rectangles(r);
    printf("%lld\n", result);
    
    return 0;
}