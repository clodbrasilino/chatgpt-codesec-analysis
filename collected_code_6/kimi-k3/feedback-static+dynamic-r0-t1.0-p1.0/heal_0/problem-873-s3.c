#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

unsigned long long fibonacci(int n) {
    if (n <= 1) {
        return (unsigned long long)n;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main(int argc, char *argv[]) {
    int n;
    char *endptr;
    long val;
    
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <non-negative integer>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    errno = 0;
    val = strtol(argv[1], &endptr, 10);
    
    if (errno != 0 || *endptr != '\0' || endptr == argv[1]) {
        fprintf(stderr, "Error: Invalid input. Please provide a valid non-negative integer.\n");
        return EXIT_FAILURE;
    }
    
    if (val < 0 || val > 93) {
        fprintf(stderr, "Error: Input must be between 0 and 93 (to prevent overflow).\n");
        return EXIT_FAILURE;
    }
    
    n = (int)val;
    printf("Fibonacci(%d) = %llu\n", n, fibonacci(n));
    
    return EXIT_SUCCESS;
}