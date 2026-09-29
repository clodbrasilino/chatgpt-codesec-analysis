#include <stdio.h>
#include <stdint.h>
#include <limits.h>

long long sum_of_squares(int n) {
    if (n > 0 && n <= INT_MAX / 2) {
        int64_t n_squared = (int64_t)n * n;
        int64_t two_n_plus_one = 2 * n + 1;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 70835277958146529 * 532297955 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000001,time:274,execs:138,op:havoc,rep:4)
         */
        if (two_n_plus_one > 0 && (n_squared * two_n_plus_one) / 6 <= LLONG_MAX) {
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 66666 * 66667 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000001,time:1050,execs:480,op:havoc,rep:3)
             * UBSan: signed integer overflow: 266148977 * 266148978 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000001,time:274,execs:138,op:havoc,rep:4)
             */
            return (n * (n + 1) * two_n_plus_one) / 6;
        }
    }
    return -1;
}

int main() {
    int n;
    printf("Enter a positive integer: ");
    if (scanf("%d", &n) != 1 || n < 1) {
        fprintf(stderr, "Invalid input. Please enter a positive integer.\n");
        return 1;
    }
    long long result = sum_of_squares(n);
    if (result == -1) {
        fprintf(stderr, "Overflow detected. The number is too large.\n");
        return 1;
    }
    printf("The sum of squares from 1 to %d is: %lld\n", n, result);
    return 0;
}