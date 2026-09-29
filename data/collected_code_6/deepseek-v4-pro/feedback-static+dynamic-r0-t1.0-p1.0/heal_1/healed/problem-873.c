#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

unsigned long long fibonacci(int n) {
    if (n < 0) {
        fprintf(stderr, "Error: negative input\n");
        exit(EXIT_FAILURE);
    }
    if (n == 0) return 0;
    if (n == 1) return 1;

    if (n > 93) {
        fprintf(stderr, "Error: input too large, would overflow\n");
        exit(EXIT_FAILURE);
    }

    unsigned long long prev = 0;
    unsigned long long curr = 1;
    for (int i = 2; i <= n; i++) {
        unsigned long long next = prev + curr;
        prev = curr;
        curr = next;
    }
    return curr;
}

int main(void) {
    long input;
    printf("Enter a non-negative integer: ");
    if (scanf("%ld", &input) != 1) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }
    if (input < 0) {
        fprintf(stderr, "Error: negative input\n");
        return EXIT_FAILURE;
    }
    if (input > INT_MAX) {
        fprintf(stderr, "Error: input too large\n");
        return EXIT_FAILURE;
    }
    int n = (int)input;
    printf("Fibonacci(%d) = %llu\n", n, fibonacci(n));
    return EXIT_SUCCESS;
}