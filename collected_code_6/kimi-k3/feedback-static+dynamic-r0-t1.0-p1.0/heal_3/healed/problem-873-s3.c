#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

unsigned long long fibonacci(int n) {
    unsigned long long a = 0, b = 1;
    int i;
    
    if (n <= 1) {
        return (unsigned long long)n;
    }
    
    for (i = 2; i <= n; i++) {
        unsigned long long temp = a + b;
        a = b;
        b = temp;
    }
    
    return b;
}

int main(int argc, const char *argv[]) {
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
    printf("%llu\n", fibonacci(n));
    
    return EXIT_SUCCESS;
}