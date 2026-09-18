#include <stdio.h>

long nth_nonagonal(long n) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 111111111111111 * 777777777777772 cannot be represented in type 'long' (AFL crash: id:000001,sig:06,src:000001,time:5183,execs:2227,op:havoc,rep:3)
     * UBSan: signed integer overflow: 9223372036854775807 * 9223372036854775796 cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000001,time:2057,execs:927,op:havoc,rep:16)
     * UBSan: signed integer overflow: 7 * 9223372036854775807 cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000001,time:2057,execs:927,op:havoc,rep:16)
     */
    return (n * (7 * n - 5)) / 2;
}

int main() {
    long n;
    printf("Enter the value of n: ");
    if(scanf("%ld", &n) != 1 || n <= 0) {
        printf("Invalid input. Please enter a positive integer.\n");
        return 1;
    }
    printf("The %ldth nonagonal number is: %ld\n", n, nth_nonagonal(n));
    return 0;
}