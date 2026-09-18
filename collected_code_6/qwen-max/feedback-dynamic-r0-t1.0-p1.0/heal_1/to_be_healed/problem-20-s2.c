#include <stdio.h>
#include <math.h>

int is_woodall(long n) {
    for (long k = 1; ; ++k) {
        /* Possible weaknesses found:
         * UBSan: 1.67174e+19 is outside the range of representable values of type 'long' (AFL crash: id:000000,sig:06,src:000004,time:447,execs:270,op:havoc,rep:4)
         */
        long woodall_number = k * pow(2, k) - 1;
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