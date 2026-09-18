#include <stdio.h>
#include <stdlib.h>

long long sum_even_in_range(long long l, long long r) {
    if (l > r) {
        return 0;
    }
    
    if (l < 0) {
        l = 0;
    }
    
    if (l % 2 != 0) {
        l++;
    }
    
    if (r % 2 != 0) {
        r--;
    }
    
    if (l > r) {
        return 0;
    }
    
    long long n = ((r - l) / 2) + 1;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 4 + 9223372036854775806 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000002,time:4536,execs:2235,op:havoc,rep:1)
     * UBSan: signed integer overflow: 4611686018427387902 * -9223372036854775806 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000002,time:4536,execs:2235,op:havoc,rep:1)
     * UBSan: signed integer overflow: 466666666666650 * 933333333333366 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000002,time:9075,execs:4432,op:havoc,rep:32)
     */
    return n * (l + r) / 2;
}

int main(void) {
    long long l;
    long long r;
    long long sum;
    
    if (scanf("%lld %lld", &l, &r) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    sum = sum_even_in_range(l, r);
    printf("%lld\n", sum);
    
    return EXIT_SUCCESS;
}