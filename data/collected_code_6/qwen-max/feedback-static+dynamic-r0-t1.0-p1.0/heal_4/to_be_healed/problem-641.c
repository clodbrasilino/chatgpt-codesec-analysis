#include <stdio.h>
#include <limits.h>
#include <inttypes.h>

long long nth_nonagonal_number(long n) {
    if (n > 0 && n <= (LONG_MAX - 5) / 14) {
        long long nn = (long long)n;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 388888888888888570 * 55555555555555510 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:492,execs:231,op:havoc,rep:8)
         */
        long long result = 7 * nn * nn - 5 * nn;
        if (result > LLONG_MAX - 1) {
            return -1;
        }
        return result / 2;
    } else {
        return -1;
    }
}

int main() {
    long n;
    printf("Enter the value of n: ");
    if (scanf("%ld", &n) == 1) {
        if (n > 0) {
            long long result = nth_nonagonal_number(n);
            if (result != -1) {
                printf("The %ldth nonagonal number is: %lld\n", n, result);
            } else {
                printf("Input too large for safe computation.\n");
            }
        } else {
            printf("Please enter a positive integer.\n");
        }
    } else {
        printf("Invalid input. Please enter an integer.\n");
    }
    return 0;
}