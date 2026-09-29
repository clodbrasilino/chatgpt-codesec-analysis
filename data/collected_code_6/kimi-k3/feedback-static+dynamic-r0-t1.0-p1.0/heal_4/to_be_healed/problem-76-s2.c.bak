#include <stdio.h>
#include <stdlib.h>

long long count_squares(long long m, long long n) {
    if (m <= 0 || n <= 0) {
        return 0;
    }
    
    if (m < n) {
        long long temp = m;
        m = n;
        n = temp;
    }
    
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 12 * 1333333333333333330 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:50530,execs:20615,op:havoc,rep:1)
     * UBSan: signed integer overflow: 3 * 9223372036854775807 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:670,execs:293,op:havoc,rep:2)
     * UBSan: signed integer overflow: 12 * 9223372036854775803 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:670,execs:293,op:havoc,rep:2)
     */
    return n * (n + 1) * (3 * m - n + 1) / 6;
}

int main(void) {
    long long m, n;
    
    if (scanf("%lld %lld", &m, &n) != 2) {
        return EXIT_FAILURE;
    }
    
    printf("%lld\n", count_squares(m, n));
    fflush(stdout);
    
    return EXIT_SUCCESS;
}