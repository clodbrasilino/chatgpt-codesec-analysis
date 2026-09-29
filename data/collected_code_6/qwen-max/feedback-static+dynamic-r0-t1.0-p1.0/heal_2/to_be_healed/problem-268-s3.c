#include <stdio.h>
#include <stdint.h>

int64_t nth_star_number(int64_t n) {
    if (n > 0 && n < 9223372036854775807 / 6 + 1) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 19999999998 * 3333333332 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000001,time:671,execs:344,op:havoc,rep:1)
         */
        return 6 * n * (n - 1) + 1;
    } else {
        return -1;
    }
}

int main() {
    int64_t n;
    printf("Enter the value of n: ");
    if (scanf("%ld", &n) != 1) {
        printf("Invalid input.\n");
        return 1;
    }
    int64_t result = nth_star_number(n);
    if (result == -1) {
        printf("Input too large to compute.\n");
        return 1;
    }
    printf("The %ldth star number is: %ld\n", n, result);
    return 0;
}