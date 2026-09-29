#include <stdio.h>

long nth_hexagonal_number(long n) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 1333333333333333332 * 1333333333333333331 cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000002,time:549,execs:215,op:havoc,rep:9)
     * UBSan: signed integer overflow: 2 * 9223372036854775807 cannot be represented in type 'long' (AFL crash: id:000001,sig:06,src:000002,time:1223,execs:443,op:havoc,rep:7)
     */
    return 2 * n * (2 * n - 1);
}

int main() {
    long n;
    printf("Enter the value of n: ");
    if (scanf("%ld", &n) == 1) {
        long hex_num = nth_hexagonal_number(n);
        printf("The %ldth hexagonal number is %ld\n", n, hex_num);
    } else {
        printf("Invalid input.\n");
    }
    return 0;
}