#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>

bool is_woodall_number(long n) {
    if (n < 1) return false;
    for (long k = 1; ; k++) {
        if (k > 62) break; // Prevent overflow
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: -9223372036854775808 - 1 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:2104,execs:997,op:havoc,rep:5)
         * UBSan: signed integer overflow: 58 * 288230376151711744 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:2104,execs:997,op:havoc,rep:5)
         */
        long woodall = k * ((long long)1 << k) - 1;
        if (woodall == n) return true;
        if (woodall > n) return false;
    }
}

int main() {
    long number;
    printf("Enter a number: ");
    if (scanf("%ld", &number) != 1) {
        printf("Invalid input.\n");
        return 1;
    }
    if (is_woodall_number(number)) {
        printf("%ld is a Woodall number.\n", number);
    } else {
        printf("%ld is not a Woodall number.\n", number);
    }
    return 0;
}