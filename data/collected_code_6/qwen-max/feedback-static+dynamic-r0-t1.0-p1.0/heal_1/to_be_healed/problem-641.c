#include <stdio.h>

long long nth_nonagonal_number(long n) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 9223372036854775801 * 9223372036854775807 cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000001,time:319,execs:155,op:havoc,rep:1)
     * UBSan: signed integer overflow: 5 * 9223372036854775807 cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000001,time:319,execs:155,op:havoc,rep:1)
     * UBSan: signed integer overflow: 77777777777770 * 11111111111110 cannot be represented in type 'long' (AFL crash: id:000001,sig:06,src:000001,time:506,execs:238,op:havoc,rep:1)
     * UBSan: signed integer overflow: 7 * 9223372036854775807 cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000001,time:319,execs:155,op:havoc,rep:1)
     */
    return (7 * n * n - 5 * n) / 2;
}

int main() {
    long n;
    printf("Enter the value of n: ");
    if (scanf("%ld", &n) == 1) {
        if (n > 0) {
            long long result = nth_nonagonal_number(n);
            printf("The %ldth nonagonal number is: %lld\n", n, result);
        } else {
            printf("Please enter a positive integer.\n");
        }
    } else {
        printf("Invalid input. Please enter an integer.\n");
    }
    return 0;
}