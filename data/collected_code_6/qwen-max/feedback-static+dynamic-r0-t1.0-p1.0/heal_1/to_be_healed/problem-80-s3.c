#include <stdio.h>
#include <stdlib.h>

long nth_tetrahedral_number(long n) {
    if (n <= 0) return 0;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 9223372036854775807 * -9223372036854775808 cannot be represented in type 'long' (AFL crash: id:000001,sig:06,src:000001,time:407,execs:190,op:havoc,rep:1)
     * UBSan: signed integer overflow: -9223372036854775808 * -9223372036854775807 cannot be represented in type 'long' (AFL crash: id:000001,sig:06,src:000001,time:407,execs:190,op:havoc,rep:1)
     * UBSan: signed integer overflow: 5555555555555555555 * 5555555555555555556 cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000001,time:381,execs:180,op:havoc,rep:2)
     * UBSan: signed integer overflow: 9223372036854775807 + 2 cannot be represented in type 'long' (AFL crash: id:000001,sig:06,src:000001,time:407,execs:190,op:havoc,rep:1)
     * UBSan: signed integer overflow: -6781775867640131028 * 5555555555555555557 cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000001,time:381,execs:180,op:havoc,rep:2)
     * UBSan: signed integer overflow: 30864196913580 * 5555557 cannot be represented in type 'long' (AFL crash: id:000002,sig:06,src:000001,time:1167,execs:499,op:havoc,rep:8)
     * UBSan: signed integer overflow: 9223372036854775807 + 1 cannot be represented in type 'long' (AFL crash: id:000001,sig:06,src:000001,time:407,execs:190,op:havoc,rep:1)
     */
    return n * (n + 1) * (n + 2) / 6;
}

int main() {
    long n;
    printf("Enter the value of n: ");
    if (scanf("%ld", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        exit(EXIT_FAILURE);
    }
    long result = nth_tetrahedral_number(n);
    printf("The %ldth tetrahedral number is: %ld\n", n, result);
    return 0;
}