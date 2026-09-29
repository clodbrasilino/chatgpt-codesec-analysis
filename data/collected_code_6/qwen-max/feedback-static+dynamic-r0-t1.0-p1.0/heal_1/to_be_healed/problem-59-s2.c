#include <stdio.h>
#include <stdlib.h>

long nth_octagonal_number(long n) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 3 * 9223372036854775807 cannot be represented in type 'long' (AFL crash: id:000001,sig:06,src:000001,time:364,execs:172,op:havoc,rep:13)
     * UBSan: signed integer overflow: 44444444444 * 133333333330 cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000001,time:343,execs:164,op:havoc,rep:8)
     * UBSan: signed integer overflow: 9223372036854775807 * 9223372036854775803 cannot be represented in type 'long' (AFL crash: id:000001,sig:06,src:000001,time:364,execs:172,op:havoc,rep:13)
     */
    return n * (3 * n - 2);
}

int main() {
    long n;
    printf("Enter a number: ");
    if(scanf("%ld", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    if(n <= 0) {
        fprintf(stderr, "Input should be a positive integer\n");
        return EXIT_FAILURE;
    }
    printf("The %ldth octagonal number is %ld\n", n, nth_octagonal_number(n));
    return EXIT_SUCCESS;
}