#include <stdio.h>
#include <stdlib.h>

long long calculate_difference(long long n) {
    if (n < 0) {
        return -1;
    }

    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 9223372036854775807 + 1 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000001,time:928,execs:503,op:havoc,rep:2)
     * UBSan: signed integer overflow: 33333333333333333 * 33333333333333334 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:66,execs:46,op:havoc,rep:1)
     * UBSan: signed integer overflow: 9223372036854775807 * -9223372036854775808 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000001,time:928,execs:503,op:havoc,rep:2)
     */
    long long sum_of_n = (n * (n + 1)) / 2;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 617284382716 * 617284382716 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:883,execs:479,op:havoc,rep:5)
     * UBSan: signed integer overflow: 4327221583266017735 * 4327221583266017735 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:66,execs:46,op:havoc,rep:1)
     * UBSan: signed integer overflow: -4611686018427387904 * -4611686018427387904 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000001,time:928,execs:503,op:havoc,rep:2)
     */
    long long squared_sum = sum_of_n * sum_of_n;

    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 9223372036854775807 + 1 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000001,time:928,execs:503,op:havoc,rep:2)
     * UBSan: signed integer overflow: 33333333333333333 * 33333333333333334 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:66,execs:46,op:havoc,rep:1)
     * UBSan: signed integer overflow: 2 * 9223372036854775807 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000001,time:928,execs:503,op:havoc,rep:2)
     * UBSan: signed integer overflow: 9223372036854775807 * -9223372036854775808 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000001,time:928,execs:503,op:havoc,rep:2)
     * UBSan: signed integer overflow: 8654443166532035470 * 66666666666666667 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:66,execs:46,op:havoc,rep:1)
     * UBSan: signed integer overflow: -9223372036854775808 * -1 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000001,time:928,execs:503,op:havoc,rep:2)
     */
    long long sum_of_squares = (n * (n + 1) * (2 * n + 1)) / 6;

    return squared_sum - sum_of_squares;
}

int main(void) {
    long long n;
    
    if (scanf("%lld", &n) != 1) {
        return EXIT_FAILURE;
    }

    if (n < 0) {
        return EXIT_FAILURE;
    }

    long long difference = calculate_difference(n);
    if (difference < 0 && n != 0) {
        return EXIT_FAILURE;
    }
    
    printf("%lld\n", difference);

    return EXIT_SUCCESS;
}