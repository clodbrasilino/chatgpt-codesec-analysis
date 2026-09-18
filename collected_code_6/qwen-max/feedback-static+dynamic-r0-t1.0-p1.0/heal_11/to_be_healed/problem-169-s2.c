#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

long long int calculate_pell_number(long n) {
    if (n < 0 || n > 92) return 0;
    if (n == 1) return 1;
    if (n == 2) return 2;

    long long int a = 0, b = 1;
    for (long i = 2; i <= n; ++i) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 2 * 4866752642924153522 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:1723,execs:832,op:havoc,rep:9)
         */
        long long int c = 2 * b + a;
        if (c < 0 || c > LLONG_MAX - a) return 0;
        a = b;
        b = c;
    }
    return b;
}

int main() {
    long n;
    printf("Enter the value of n: ");
    if (scanf("%ld", &n) != 1 || n < 0 || n > 92) {
        fprintf(stderr, "Invalid input. Please enter a non-negative integer less than or equal to 92.\n");
        return EXIT_FAILURE;
    }

    long long int result = calculate_pell_number(n);
    if (result == 0) {
        fprintf(stderr, "Calculation overflowed. Please enter a smaller value of n.\n");
        return EXIT_FAILURE;
    }

    printf("The %ldth Pell number is: %lld\n", n, result);
    return 0;
}