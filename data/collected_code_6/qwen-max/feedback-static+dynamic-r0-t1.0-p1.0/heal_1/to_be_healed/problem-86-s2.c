#include <stdio.h>

long nth_centered_hexagonal(long n) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 9223372036854775805 * 9223372036854775806 cannot be represented in type 'long' (AFL crash: id:000001,sig:06,src:000000,time:2619,execs:963,op:havoc,rep:2)
     * UBSan: signed integer overflow: 3 * 9223372036854775807 cannot be represented in type 'long' (AFL crash: id:000001,sig:06,src:000000,time:2619,execs:963,op:havoc,rep:2)
     * UBSan: signed integer overflow: 6666666666666666666 * 2222222222222222221 cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000002,time:358,execs:159,op:havoc,rep:1)
     */
    return 3 * n * (n - 1) + 1;
}

int main() {
    long n;
    printf("Enter the value of n: ");
    if(scanf("%ld", &n) != 1) {
        fprintf(stderr, "Input error\n");
        return 1;
    }
    printf("The %ldth centered hexagonal number is: %ld\n", n, nth_centered_hexagonal(n));
    return 0;
}