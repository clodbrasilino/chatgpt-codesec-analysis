#include <stdio.h>

long long cube_sum_odd(int n) {
    long long sum = 0;
    int i;
    for (i = 0; i < n; i++) {
        long long odd = 2LL * i + 1;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 4398050705409 * 2097153 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000005,time:2879,execs:1178,op:havoc,rep:9)
         * UBSan: signed integer overflow: 9222615723651324400 + 796108265857241 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000005,time:2879,execs:1178,op:havoc,rep:9)
         */
        sum += odd * odd * odd;
    }
    return sum;
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    if (n < 0) {
        fprintf(stderr, "n must be non-negative\n");
        return 1;
    }
    printf("%lld\n", cube_sum_odd(n));
    return 0;
}