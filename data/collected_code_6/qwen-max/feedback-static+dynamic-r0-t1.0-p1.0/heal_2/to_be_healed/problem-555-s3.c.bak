#include <stdio.h>

long long sum_of_cubes(long n) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 33333333333 * 33333333334 cannot be represented in type 'long' (AFL crash: id:000002,sig:06,src:000000,time:2365,execs:1092,op:havoc,rep:7)
     * UBSan: signed integer overflow: 2153233349824562631 * 2153233349824562631 cannot be represented in type 'long' (AFL crash: id:000002,sig:06,src:000000,time:2365,execs:1092,op:havoc,rep:7)
     * UBSan: signed integer overflow: 14222223111111 * 14222223111111 cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000001,time:258,execs:141,op:havoc,rep:3)
     * UBSan: signed integer overflow: -4611686018427387904 * -4611686018427387904 cannot be represented in type 'long' (AFL crash: id:000001,sig:06,src:000001,time:272,execs:145,op:havoc,rep:3)
     * UBSan: signed integer overflow: 9223372036854775807 * -9223372036854775808 cannot be represented in type 'long' (AFL crash: id:000001,sig:06,src:000001,time:272,execs:145,op:havoc,rep:3)
     * UBSan: signed integer overflow: 9223372036854775807 + 1 cannot be represented in type 'long' (AFL crash: id:000001,sig:06,src:000001,time:272,execs:145,op:havoc,rep:3)
     */
    return (n * (n + 1) / 2) * (n * (n + 1) / 2);
}

long long sum_of_numbers(long n) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 33333333333 * 33333333334 cannot be represented in type 'long' (AFL crash: id:000002,sig:06,src:000000,time:2365,execs:1092,op:havoc,rep:7)
     * UBSan: signed integer overflow: 9223372036854775807 * -9223372036854775808 cannot be represented in type 'long' (AFL crash: id:000001,sig:06,src:000001,time:272,execs:145,op:havoc,rep:3)
     * UBSan: signed integer overflow: 9223372036854775807 + 1 cannot be represented in type 'long' (AFL crash: id:000001,sig:06,src:000001,time:272,execs:145,op:havoc,rep:3)
     */
    return (n * (n + 1)) / 2;
}

long long difference(long n) {
    return sum_of_cubes(n) - sum_of_numbers(n);
}

int main() {
    long n;
    printf("Enter a natural number: ");
    if (scanf("%ld", &n) != 1) {
        printf("Invalid input. Please enter a valid natural number.\n");
        return 1;
    }

    if (n < 1) {
        printf("Please enter a valid natural number.\n");
        return 1;
    }

    long long diff = difference(n);
    printf("The difference is: %lld\n", diff);
    return 0;
}