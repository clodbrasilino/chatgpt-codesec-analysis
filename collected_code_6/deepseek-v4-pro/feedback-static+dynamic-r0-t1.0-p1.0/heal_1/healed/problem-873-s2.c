#include <stdio.h>
#include <stdlib.h>

unsigned long long fibonacci(int n) {
    if (n < 0) {
        fprintf(stderr, "Error: Input must be non-negative\n");
        exit(EXIT_FAILURE);
    }
    
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    
    unsigned long long prev2 = 0;
    unsigned long long prev1 = 1;
    unsigned long long current = 0;
    
    for (int i = 2; i <= n; i++) {
        current = prev1 + prev2;
        prev2 = prev1;
        prev1 = current;
    }
    
    return current;
}

int main(void) {
    int n;
    
    printf("Enter a non-negative integer: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Error: Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (n < 0) {
        fprintf(stderr, "Error: Input must be non-negative\n");
        return EXIT_FAILURE;
    }
    
    unsigned long long result = fibonacci(n);
    printf("Fibonacci(%d) = %llu\n", n, result);
    
    return EXIT_SUCCESS;
}