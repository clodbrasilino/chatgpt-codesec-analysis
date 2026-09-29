#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

bool isFactorialDivisibleByX(long n, long x) {
    long product = 1;
    for (long i = 1; i <= n; i++) {
        if (product > LONG_MAX / i) return false;
        product *= i;
        if (product % x == 0) return true;
    }
    return false;
}

int findFirstFactorialDivisibleByX(long x) {
    long n = 1;
    while (true) {
        if (isFactorialDivisibleByX(n, x)) {
            return n;
        }
        n++;
    }
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