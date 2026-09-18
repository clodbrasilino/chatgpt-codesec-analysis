#include <stdio.h>
#include <stdlib.h>

long long calculate_difference(long long n) {
    if (n < 0) {
        return -1; 
    }
    
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 125713709145156 * 22424425 cannot be represented in type 'long long' (AFL crash: id:000003,sig:06,src:000001,time:2624,execs:1383,op:havoc,rep:2)
     * UBSan: signed integer overflow: 1111111111111111111 * 1111111111111111112 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:1336,execs:712,op:havoc,rep:2)
     * UBSan: signed integer overflow: 2 * 9223372036854775807 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:779,execs:420,op:havoc,rep:3)
     * UBSan: signed integer overflow: 9223372036854775807 + 1 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:779,execs:420,op:havoc,rep:3)
     * UBSan: signed integer overflow: -8236819301197301128 * 2222222222222222223 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:1336,execs:712,op:havoc,rep:2)
     * UBSan: signed integer overflow: 9223372036854775807 * -9223372036854775808 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:779,execs:420,op:havoc,rep:3)
     * UBSan: signed integer overflow: -9223372036854775808 * -1 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:779,execs:420,op:havoc,rep:3)
     */
    long long sum_of_squares = (n * (n + 1) * (2 * n + 1)) / 6;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 9223372036854775807 + 1 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:779,execs:420,op:havoc,rep:3)
     * UBSan: signed integer overflow: 1111111111111111111 * 1111111111111111112 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:1336,execs:712,op:havoc,rep:2)
     * UBSan: signed integer overflow: 9223372036854775807 * -9223372036854775808 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:779,execs:420,op:havoc,rep:3)
     */
    long long sum = (n * (n + 1)) / 2;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: -4611686018427387904 * -4611686018427387904 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:779,execs:420,op:havoc,rep:3)
     * UBSan: signed integer overflow: -4118409650598650564 * -4118409650598650564 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:1336,execs:712,op:havoc,rep:2)
     * UBSan: signed integer overflow: 617284382716 * 617284382716 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000001,time:2534,execs:1339,op:havoc,rep:4)
     * UBSan: signed integer overflow: 62856854572578 * 62856854572578 cannot be represented in type 'long long' (AFL crash: id:000003,sig:06,src:000001,time:2624,execs:1383,op:havoc,rep:2)
     */
    long long square_of_sum = sum * sum;
    
    return square_of_sum - sum_of_squares;
}

int main(void) {
    long long n;
    long long result;

    if (scanf("%lld", &n) != 1) {
        return EXIT_FAILURE;
    }

    result = calculate_difference(n);
    if (result == -1) {
        return EXIT_FAILURE;
    }

    printf("%lld\n", result);

    return EXIT_SUCCESS;
}