#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

bool is_woodall_number(long n) {
    if (n <= 0) return false;
    for (long k = 1; ; k++) {
        long woodall;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: -9223372036854775808 - 1 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:650,execs:417,op:havoc,rep:5)
         * UBSan: signed integer overflow: 58 * 288230376151711744 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:650,execs:417,op:havoc,rep:5)
         */
        if (k < LONG_MAX / 2 && (woodall = k * (1LL << k) - 1) > n) break;
        if (woodall == n) return true;
    }
    return false;
}

int main() {
    long number;
    printf("Enter a number: ");
    scanf("%ld", &number);
    if (is_woodall_number(number)) {
        printf("%ld is a Woodall number.\n", number);
    } else {
        printf("%ld is not a Woodall number.\n", number);
    }
    return 0;
}