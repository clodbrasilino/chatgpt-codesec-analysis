#include <stdio.h>

long nth_tetrahedral_number(long n) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 9223372036854775807 + 1 cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000000,time:624,execs:274,op:havoc,rep:2)
     * UBSan: signed integer overflow: -9223372036854775808 * -9223372036854775807 cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000000,time:624,execs:274,op:havoc,rep:2)
     * UBSan: signed integer overflow: 4639255188011504172 * 5855555555555555557 cannot be represented in type 'long' (AFL crash: id:000001,sig:06,src:000000,time:1393,execs:586,op:havoc,rep:6)
     * UBSan: signed integer overflow: 9223372036854775807 * -9223372036854775808 cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000000,time:624,execs:274,op:havoc,rep:2)
     * UBSan: signed integer overflow: 5855555555555555555 * 5855555555555555556 cannot be represented in type 'long' (AFL crash: id:000001,sig:06,src:000000,time:1393,execs:586,op:havoc,rep:6)
     * UBSan: signed integer overflow: 11111112222222 * 3333335 cannot be represented in type 'long' (AFL crash: id:000002,sig:06,src:000001,time:4861,execs:2065,op:havoc,rep:3)
     * UBSan: signed integer overflow: 9223372036854775807 + 2 cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000000,time:624,execs:274,op:havoc,rep:2)
     */
    return (n * (n + 1) * (n + 2)) / 6;
}

int main() {
    long n;
    printf("Enter the value of n: ");
    if (scanf("%ld", &n) != 1 || n < 0) {
        fprintf(stderr, "Invalid input. Please enter a non-negative integer.\n");
        return 1;
    }
    long result = nth_tetrahedral_number(n);
    printf("The %ldth tetrahedral number is: %ld\n", n, result);
    return 0;
}