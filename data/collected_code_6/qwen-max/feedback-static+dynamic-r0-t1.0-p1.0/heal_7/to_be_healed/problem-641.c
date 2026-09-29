#include <stdio.h>
#include <limits.h>
#include <inttypes.h>

long long nth_nonagonal_number(long n) {
    if (n > 0 && n <= (LONG_MAX - 5) / 14) {
        long long nn = (long long)n;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 3888888888885 * 555555555555 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:906,execs:457,op:havoc,rep:1)
         */
        long long result1 = 7 * nn * nn;
        long long result2 = 5 * nn;
        if (result1 < 0 || result2 < 0 || (result1 - result2) < 0 || (result1 - result2) % 2 != 0) {
            return -1;
        }
        long long result = (result1 - result2) / 2;
        if (result > LLONG_MAX) {
            return -1;
        }
        return result;
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