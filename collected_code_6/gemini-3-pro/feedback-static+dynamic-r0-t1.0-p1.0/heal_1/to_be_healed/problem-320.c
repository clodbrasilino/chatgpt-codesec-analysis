#include <stdio.h>
#include <stdlib.h>

long long calculate_difference(long long n) {
    if (n < 0) {
        return -1;
    }

    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 9223372036854775807 + 1 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:396,execs:222,op:havoc,rep:3)
     * UBSan: signed integer overflow: 9223372036854775807 * -9223372036854775808 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:396,execs:222,op:havoc,rep:3)
     * UBSan: signed integer overflow: 111111111111111111 * 111111111111111112 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:339,execs:193,op:havoc,rep:3)
     */
    long long sum = (n * (n + 1)) / 2;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 920041996068379964 * 920041996068379964 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:339,execs:193,op:havoc,rep:3)
     * UBSan: signed integer overflow: -4611686018427387904 * -4611686018427387904 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:396,execs:222,op:havoc,rep:3)
     * UBSan: signed integer overflow: 6172882716 * 6172882716 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000001,time:417,execs:230,op:havoc,rep:5)
     */
    long long squared_sum = sum * sum;
    
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 111111111111111111 * 111111111111111112 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:339,execs:193,op:havoc,rep:3)
     * UBSan: signed integer overflow: 9223372036854775807 + 1 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:396,execs:222,op:havoc,rep:3)
     * UBSan: signed integer overflow: 2 * 9223372036854775807 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:396,execs:222,op:havoc,rep:3)
     * UBSan: signed integer overflow: 1840083992136759928 * 222222222222222223 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:339,execs:193,op:havoc,rep:3)
     * UBSan: signed integer overflow: -9223372036854775808 * -1 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:396,execs:222,op:havoc,rep:3)
     * UBSan: signed integer overflow: 9223372036854775807 * -9223372036854775808 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:396,execs:222,op:havoc,rep:3)
     */
    long long sum_of_squares = (n * (n + 1) * (2 * n + 1)) / 6;

    return squared_sum - sum_of_squares;
}

int main(void) {
    long long n;
    
    if (scanf("%lld", &n) != 1) {
        return EXIT_FAILURE;
    }

    long long result = calculate_difference(n);
    if (result == -1) {
        return EXIT_FAILURE;
    }

    printf("%lld\n", result);

    return EXIT_SUCCESS;
}