#include <stdio.h>
#include <stdlib.h>

long long sum_odd_natural_numbers(long long l, long long r) {
    if (l > r) {
        return 0;
    }
    
    long long first_odd = (l % 2 == 0) ? l + 1 : l;
    
    if (first_odd > r) {
        return 0;
    }
    
    long long last_odd = (r % 2 == 0) ? r - 1 : r;
    long long count = (last_odd - first_odd) / 2 + 1;
    
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 3 + 9223372036854775807 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000005,time:19086,execs:7870,op:havoc,rep:3)
     * UBSan: signed integer overflow: 4611686018427387903 * -9223372036854775806 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000005,time:19086,execs:7870,op:havoc,rep:3)
     * UBSan: signed integer overflow: 1111111111110 * 2222222222224 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000006,time:14305,execs:5635,op:havoc,rep:2)
     */
    return count * (first_odd + last_odd) / 2;
}

int main(void) {
    long long l, r;
    
    if (scanf("%lld %lld", &l, &r) != 2) {
        return EXIT_FAILURE;
    }
    
    printf("%lld\n", sum_odd_natural_numbers(l, r));
    
    return EXIT_SUCCESS;
}