#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

long long nth_octagonal_number(long long n) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 3 * 9223372036854775807 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:289,execs:157,op:havoc,rep:1)
     * UBSan: signed integer overflow: 555555555555555555 * 1666666666666666663 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:574,execs:298,op:havoc,rep:2)
     * UBSan: signed integer overflow: 9223372036854775807 * 9223372036854775803 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:289,execs:157,op:havoc,rep:1)
     */
    return n * (3LL * n - 2LL);
}

int main() {
    long long n;
    printf("Enter a number: ");
    if(scanf("%lld", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    if(n <= 0) {
        fprintf(stderr, "Input should be a positive integer\n");
        return EXIT_FAILURE;
    }
    printf("The %lldth octagonal number is %lld\n", n, nth_octagonal_number(n));
    return EXIT_SUCCESS;
}