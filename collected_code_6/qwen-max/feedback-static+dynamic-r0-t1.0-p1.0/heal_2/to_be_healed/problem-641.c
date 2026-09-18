#include <stdio.h>
#include <limits.h>

long long nth_nonagonal_number(long n) {
    if (n > 0 && n <= (LONG_MAX - 5) / 14) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 77777777777770 * 11111111111110 cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000001,time:531,execs:265,op:havoc,rep:1)
         */
        return (7 * n * n - 5 * n) / 2;
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