#include <stdio.h>
#include <stdlib.h>

long long sum_of_odds(long long l, long long r) {
    if (l > r) {
        return 0;
    }
    
    if (l < 0) {
        l = 0;
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
     * UBSan: signed integer overflow: 1111111111111111112 * 2222222222222222228 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:984,execs:469,op:havoc,rep:2)
     * UBSan: signed integer overflow: 2611111110 * 5222222224 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:772,execs:376,op:havoc,rep:1)
     * UBSan: signed integer overflow: 3 + 9223372036854775807 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000001,time:1034,execs:493,op:havoc,rep:2)
     * UBSan: signed integer overflow: 4611686018427387903 * -9223372036854775806 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000001,time:1034,execs:493,op:havoc,rep:2)
     */
    return n * (l + r) / 2;
}

int main(void) {
    long long l, r;
    
    if (scanf("%lld %lld", &l, &r) != 2) {
        return EXIT_FAILURE;
    }
    
    long long result = sum_of_odds(l, r);
    printf("%lld\n", result);
    
    return EXIT_SUCCESS;
}