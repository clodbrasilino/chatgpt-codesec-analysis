#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long perrin_number(long n) {
    if (n < 0 || n > LLONG_MAX) return -1;
    if (n == 0) return 3;
    if (n == 1) return 0;
    if (n == 2) return 2;

    long long a = 3, b = 0, c = 2;
    for (long i = 3; i <= n; ++i) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 4840428246616975367 + 6412202219048207347 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:800,execs:352,op:havoc,rep:5)
         */
        long long d = a + b;
        a = b;
        b = c;
        c = d;
    }
    return c;
}

long long sum_perrin_numbers(long n) {
    if (n < 0 || n > LLONG_MAX) return -1;
    long long sum = 0;
    for (long i = 0; i <= n; ++i) {
        long long pnum = perrin_number(i);
        if (pnum == -1) return -1;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 8494359425057768730 + 2758271040607413982 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:800,execs:352,op:havoc,rep:5)
         */
        sum += pnum;
    }
    return sum;
}

int main() {
    long n;
    printf("Enter the value of n: ");
    if (scanf("%ld", &n) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    long long result = sum_perrin_numbers(n);
    if (result == -1) {
        fprintf(stderr, "Input out of range or error occurred.\n");
        return EXIT_FAILURE;
    }
    
    printf("Sum of Perrin numbers up to P(%ld): %lld\n", n, result);
    
    return EXIT_SUCCESS;
}