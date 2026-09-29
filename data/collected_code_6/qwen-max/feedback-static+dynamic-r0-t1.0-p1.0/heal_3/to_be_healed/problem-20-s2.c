#include <stdio.h>
#include <math.h>
#include <limits.h>

int is_woodall(long n) {
    for (long k = 1; ; ++k) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 58 * 288230376151711744 cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000001,time:817,execs:391,op:havoc,rep:2)
         */
        long woodall_number = k * (1L << k) - 1;
        if (woodall_number == n) return 1;
        if (woodall_number > n || woodall_number < 0) break;
    }
    return 0;
}

int main() {
    long number;
    printf("Enter a number: ");
    scanf("%ld", &number);

    if (is_woodall(number)) {
        printf("%ld is a Woodall number.\n", number);
    } else {
        printf("%ld is not a Woodall number.\n", number);
    }

    return 0;
}