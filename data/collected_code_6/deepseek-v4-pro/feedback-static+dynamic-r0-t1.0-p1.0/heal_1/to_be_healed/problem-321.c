#include <stdio.h>
#include <stdlib.h>

long long demlo_number(int n) {
    if (n <= 0) {
        return 0;
    }
    long long result = 0;
    long long term = 0;
    for (int i = 1; i <= n; i++) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 1111111111111111111 * 10 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:134,execs:64,op:havoc,rep:6)
         */
        term = term * 10 + 1;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 4807227033988981239 + 6371555158481727943 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:134,execs:64,op:havoc,rep:6)
         */
        result += term;
    }
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 9109503246276320551 * 9109503246276320551 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:134,execs:64,op:havoc,rep:6)
     * UBSan: signed integer overflow: 12345679011 * 12345679011 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000000,time:191,execs:88,op:havoc,rep:5)
     */
    return result * result;
}

int main(void) {
    int num;
    printf("Enter a number: ");
    if (scanf("%d", &num) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    if (num < 0) {
        fprintf(stderr, "Number must be non-negative\n");
        return EXIT_FAILURE;
    }
    printf("%lld\n", demlo_number(num));
    return EXIT_SUCCESS;
}