#include <stdio.h>

long nth_hexagonal_number(long n) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 2 * 9223372036854775807 cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000002,time:843,execs:318,op:havoc,rep:1)
     * UBSan: signed integer overflow: 55555555555 * 111111111109 cannot be represented in type 'long' (AFL crash: id:000001,sig:06,src:000002,time:942,execs:350,op:havoc,rep:1)
     * UBSan: signed integer overflow: 9223372036854775807 * -3 cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000002,time:843,execs:318,op:havoc,rep:1)
     */
    return n * (2 * n - 1);
}

int main() {
    long n;
    printf("Enter the value of n: ");
    if (scanf("%ld", &n) == 1 && n > 0) {
        long hex_num = nth_hexagonal_number(n);
        printf("The %ldth hexagonal number is: %ld\n", n, hex_num);
    } else {
        printf("Invalid input. Please enter a positive integer.\n");
    }
    return 0;
}