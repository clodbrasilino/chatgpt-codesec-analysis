#include <stdio.h>
#include <limits.h>

long long square_sum(long long n) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: -4611686018427387904 * -4611686018427387904 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000000,time:16772,execs:7151,op:havoc,rep:6)
     * UBSan: signed integer overflow: 9223372036854775807 * -9223372036854775808 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000000,time:16772,execs:7151,op:havoc,rep:6)
     * UBSan: signed integer overflow: 9223372036854775807 + 1 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000000,time:16772,execs:7151,op:havoc,rep:6)
     * UBSan: signed integer overflow: 1111111111111111112 * 1111111111111111113 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:626,execs:298,op:havoc,rep:1)
     * UBSan: signed integer overflow: 6172839549382716 * 6172839549382716 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:7473,execs:3171,op:havoc,rep:10)
     * UBSan: signed integer overflow: -3007298539487539452 * -3007298539487539452 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:626,execs:298,op:havoc,rep:1)
     */
    return (n * (n + 1) / 2) * (n * (n + 1) / 2);
}

long long sum_of_squares(long long n) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 12345679098765432 * 222222223 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:7473,execs:3171,op:havoc,rep:10)
     * UBSan: signed integer overflow: 9223372036854775807 * -9223372036854775808 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000000,time:16772,execs:7151,op:havoc,rep:6)
     * UBSan: signed integer overflow: 2 * 9223372036854775807 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000000,time:16772,execs:7151,op:havoc,rep:6)
     * UBSan: signed integer overflow: 9223372036854775807 + 1 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000000,time:16772,execs:7151,op:havoc,rep:6)
     * UBSan: signed integer overflow: 1111111111111111112 * 1111111111111111113 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:626,execs:298,op:havoc,rep:1)
     * UBSan: signed integer overflow: -9223372036854775808 * -1 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000000,time:16772,execs:7151,op:havoc,rep:6)
     * UBSan: signed integer overflow: -6014597078975078904 * 2222222222222222225 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:626,execs:298,op:havoc,rep:1)
     */
    return n * (n + 1) * (2 * n + 1) / 6;
}

long long calculate_difference(long long n) {
    if (n <= 0) {
        return -1; // Indicate invalid input
    }
    return square_sum(n) - sum_of_squares(n);
}

int main() {
    long long n, result;
    printf("Enter a positive integer: ");
    if (scanf("%lld", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input. Please enter a positive integer.\n");
        return 1;
    }
    result = calculate_difference(n);
    if (result == -1) {
        fprintf(stderr, "Calculation error.\n");
        return 1;
    }
    printf("The result is: %lld\n", result);
    return 0;
}