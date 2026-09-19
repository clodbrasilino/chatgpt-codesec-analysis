#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <limits.h>

long long int calculate_pell_number(long n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;
    if (n == 2) return 2;

    long long int a = 0, b = 1;
    for (long i = 2; i <= n; ++i) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 5052016396815640554 + 4866752642924153522 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000002,time:115,execs:148,op:havoc,rep:4)
         * UBSan: signed integer overflow: 2 * 4866752642924153522 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000002,time:115,execs:148,op:havoc,rep:4)
         */
        long long int c = 2 * b + a;
        if (c > LLONG_MAX || c < LLONG_MIN) {
            fprintf(stderr, "Overflow detected.\n");
            exit(EXIT_FAILURE);
        }
        a = b;
        b = c;
    }
    return b;
}

int main() {
    long n;
    printf("Enter the value of n: ");
    if (scanf("%ld", &n) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }

    long long int result = calculate_pell_number(n);
    printf("The %ldth Pell number is: %lld\n", n, result);

    return 0;
}