#include <stdio.h>
#include <stdint.h>

long long sum_of_cubes(long n) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 9223372036854775807 * -9223372036854775808 cannot be represented in type 'long' (AFL crash: id:000001,sig:06,src:000001,time:1754,execs:1034,op:havoc,rep:1)
     * UBSan: signed integer overflow: 111111111111111 * 111111111111112 cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000000,time:366,execs:231,op:havoc,rep:8)
     * UBSan: signed integer overflow: 9223372036854775807 + 1 cannot be represented in type 'long' (AFL crash: id:000001,sig:06,src:000001,time:1754,execs:1034,op:havoc,rep:1)
     */
    int64_t temp = n * (n + 1) / 2;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 2764233345921817916 * 2764233345921817916 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000000,time:366,execs:231,op:havoc,rep:8)
     * UBSan: signed integer overflow: 395061728049382716 * 395061728049382716 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000002,sig:06,src:000000,time:3687,execs:2175,op:havoc,rep:1)
     * UBSan: signed integer overflow: -4611686018427387904 * -4611686018427387904 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000001,time:1754,execs:1034,op:havoc,rep:1)
     */
    return temp * temp;
}

long long sum_of_numbers(long n) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 9223372036854775807 * -9223372036854775808 cannot be represented in type 'long' (AFL crash: id:000001,sig:06,src:000001,time:1754,execs:1034,op:havoc,rep:1)
     * UBSan: signed integer overflow: 111111111111111 * 111111111111112 cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000000,time:366,execs:231,op:havoc,rep:8)
     * UBSan: signed integer overflow: 9223372036854775807 + 1 cannot be represented in type 'long' (AFL crash: id:000001,sig:06,src:000001,time:1754,execs:1034,op:havoc,rep:1)
     */
    int64_t temp = n * (n + 1);
    return temp / 2;
}

long long difference(long n) {
    return sum_of_cubes(n) - sum_of_numbers(n);
}

int main() {
    long n;
    printf("Enter a natural number: ");
    if (scanf("%ld", &n) != 1 || n < 1) {
        printf("Invalid input. Please enter a valid natural number.\n");
        return 1;
    }

    long long diff = difference(n);
    printf("The difference is: %lld\n", diff);
    return 0;
}