#include <stdio.h>
#include <stdbool.h>

bool is_woodall(long n) {
    if (n < 1) return false;
    for (long k = 1; ; k++) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: -9223372036854775808 - 1 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:979,execs:452,op:havoc,rep:2)
         * UBSan: signed integer overflow: 58 * 288230376151711744 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:979,execs:452,op:havoc,rep:2)
         */
        long long woodall_number = (long long)k * (1LL << k) - 1;
        if (woodall_number == n) return true;
        if (woodall_number > n) return false;
    }
}

int main() {
    long number;
    printf("Enter a number: ");
    if (scanf("%ld", &number) != 1) {
        printf("Invalid input.\n");
        return 1;
    }
    if (is_woodall(number)) {
        printf("%ld is a Woodall number.\n", number);
    } else {
        printf("%ld is not a Woodall number.\n", number);
    }
    return 0;
}