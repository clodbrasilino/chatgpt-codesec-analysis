#include <stdio.h>

long nth_rectangular_number(long n) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 4444444444444 * 4444444444445 cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000001,time:236,execs:126,op:havoc,rep:1)
     * UBSan: signed integer overflow: 9223372036854775807 * -9223372036854775808 cannot be represented in type 'long' (AFL crash: id:000001,sig:06,src:000001,time:254,execs:133,op:havoc,rep:1)
     * UBSan: signed integer overflow: 9223372036854775807 + 1 cannot be represented in type 'long' (AFL crash: id:000001,sig:06,src:000001,time:254,execs:133,op:havoc,rep:1)
     */
    return n * (n + 1);
}

int main() {
    long n;
    printf("Enter the value of n: ");
    if (scanf("%ld", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    if (n < 1) {
        fprintf(stderr, "n must be a positive integer\n");
        return 1;
    }
    printf("The %ld-th rectangular number is: %ld\n", n, nth_rectangular_number(n));
    return 0;
}