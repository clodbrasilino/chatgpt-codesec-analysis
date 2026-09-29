#include <stdio.h>
#include <stdlib.h>

long long int nth_star_number(long long int n) {
    if (n < 1) {
        return 0;
    }
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 6 * 9223372036854775807 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:1210,execs:523,op:havoc,rep:4)
     * UBSan: signed integer overflow: -6 * 9223372036854775806 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:1210,execs:523,op:havoc,rep:4)
     * UBSan: signed integer overflow: 26666666666664 * 4444444444443 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:374,execs:178,op:havoc,rep:4)
     */
    return 6 * n * (n - 1) + 1;
}

int main(void) {
    long long int n;
    
    if (scanf("%lld", &n) != 1) {
        return EXIT_FAILURE;
    }

    if (n < 1) {
        return EXIT_FAILURE;
    }

    long long int result = nth_star_number(n);
    printf("%lld\n", result);

    return EXIT_SUCCESS;
}