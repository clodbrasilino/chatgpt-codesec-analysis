#include <stdio.h>

long long difference_square_sum(long long n) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 9223372036854775807 * -9223372036854775808 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:476,execs:214,op:havoc,rep:13)
     * UBSan: signed integer overflow: 22222222222222222 * 22222222222222223 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:280,execs:136,op:havoc,rep:3)
     * UBSan: signed integer overflow: 9223372036854775807 + 1 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:476,execs:214,op:havoc,rep:13)
     */
    long long sum = n * (n + 1) / 2;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: -4611686018427387904 * -4611686018427387904 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:476,execs:214,op:havoc,rep:13)
     * UBSan: signed integer overflow: -2172363164557966551 * -2172363164557966551 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:280,execs:136,op:havoc,rep:3)
     * UBSan: signed integer overflow: 61728399382716 * 61728399382716 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000001,time:716,execs:304,op:havoc,rep:7)
     */
    long long square_sum = sum * sum;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: -9223372036854775808 * -1 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:476,execs:214,op:havoc,rep:13)
     * UBSan: signed integer overflow: 9223372036854775807 * -9223372036854775808 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:476,execs:214,op:havoc,rep:13)
     * UBSan: signed integer overflow: 22222222222222222 * 22222222222222223 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:280,execs:136,op:havoc,rep:3)
     * UBSan: signed integer overflow: 9223372036854775807 + 1 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:476,execs:214,op:havoc,rep:13)
     * UBSan: signed integer overflow: 2 * 9223372036854775807 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:476,execs:214,op:havoc,rep:13)
     * UBSan: signed integer overflow: 123456798765432 * 22222223 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000001,time:716,execs:304,op:havoc,rep:7)
     * UBSan: signed integer overflow: -4344726329115933102 * 44444444444444445 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:280,execs:136,op:havoc,rep:3)
     */
    long long sum_squares = n * (n + 1) * (2 * n + 1) / 6;
    return square_sum - sum_squares;
}

int main(void) {
    long long n;
    printf("Enter a natural number n: ");
    if (scanf("%lld", &n) != 1 || n < 1) {
        printf("Invalid input. Please enter a valid natural number.\n");
        return 1;
    }

    long long result = difference_square_sum(n);
    printf("Difference: %lld\n", result);

    return 0;
}