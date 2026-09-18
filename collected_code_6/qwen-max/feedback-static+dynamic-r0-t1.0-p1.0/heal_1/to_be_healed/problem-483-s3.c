#include <stdio.h>
#include <stdlib.h>

long factorial(long n) {
    if (n == 0) return 1;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 21 * 2432902008176640000 cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000003,time:305,execs:141,op:havoc,rep:2)
     */
    return n * factorial(n - 1);
}

int findFirstFactorialDivisibleByX(long x) {
    long n = 1;
    while (1) {
        long fact = factorial(n);
        if (fact % x == 0) {
            return n;
        }
        n++;
    }
    return -1; // Unreachable, but to avoid compiler warnings
}

int main() {
    long x;
    printf("Enter a number: ");
    if (scanf("%ld", &x) != 1 || x <= 0) {
        fprintf(stderr, "Invalid input. Please enter a positive integer.\n");
        return EXIT_FAILURE;
    }
    int result = findFirstFactorialDivisibleByX(x);
    printf("The first natural number whose factorial is divisible by %ld is: %d\n", x, result);
    return EXIT_SUCCESS;
}