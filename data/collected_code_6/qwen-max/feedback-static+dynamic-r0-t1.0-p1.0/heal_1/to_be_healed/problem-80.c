#include <stdio.h>

long long nth_tetrahedral_number(long n) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 9223372036854775807 + 2 cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000001,time:616,execs:261,op:havoc,rep:8)
     * UBSan: signed integer overflow: 9223372036854775807 * -9223372036854775808 cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000001,time:616,execs:261,op:havoc,rep:8)
     * UBSan: signed integer overflow: 4938272839506 * 2222224 cannot be represented in type 'long' (AFL crash: id:000002,sig:06,src:000000,time:7863,execs:3065,op:havoc,rep:16)
     * UBSan: signed integer overflow: 111111111511 * 111111111512 cannot be represented in type 'long' (AFL crash: id:000001,sig:06,src:000000,time:1873,execs:703,op:havoc,rep:5)
     * UBSan: signed integer overflow: -9223372036854775808 * -9223372036854775807 cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000001,time:616,execs:261,op:havoc,rep:8)
     * UBSan: signed integer overflow: 9223372036854775807 + 1 cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000001,time:616,execs:261,op:havoc,rep:8)
     * UBSan: signed integer overflow: 4807316009297783528 * 111111111513 cannot be represented in type 'long' (AFL crash: id:000001,sig:06,src:000000,time:1873,execs:703,op:havoc,rep:5)
     */
    return (n * (n + 1) * (n + 2)) / 6;
}

int main() {
    long n;
    printf("Enter the value of n: ");
    if (scanf("%ld", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    printf("The %ldth tetrahedral number is: %lld\n", n, nth_tetrahedral_number(n));
    return 0;
}