#include <stdio.h>
#include <stdlib.h>

long long perrin_number(long n) {
    if (n == 0) return 3;
    if (n == 1) return 0;
    if (n == 2) return 2;

    long long a = 3, b = 0, c = 2;
    for (long i = 3; i <= n; ++i) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 4840428246616975367 + 6412202219048207347 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:305,execs:315,op:havoc,rep:9)
         */
        long long d = a + b;
        a = b;
        b = c;
        c = d;
    }
    return c;
}

long long sum_perrin_numbers(long n) {
    long long sum = 0;
    for (long i = 0; i <= n; ++i) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 8494359425057768730 + 2758271040607413982 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:305,execs:315,op:havoc,rep:9)
         */
        sum += perrin_number(i);
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
    printf("Sum of Perrin numbers up to P(%ld): %lld\n", n, result);
    
    return EXIT_SUCCESS;
}