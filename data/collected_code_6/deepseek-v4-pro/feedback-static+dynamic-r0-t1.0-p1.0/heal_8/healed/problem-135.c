#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long hexagonal_number(int n) {
    if (n <= 0) {
        return -1;
    }
    return (long long)n * (2 * (long long)n - 1);
}

int main(int argc, char *const argv[]) {
    int n;
    
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    
    if (*endptr != '\0' || endptr == argv[1]) {
        fprintf(stderr, "Error: Invalid integer input\n");
        return EXIT_FAILURE;
    }
    
    if (val > INT_MAX || val < INT_MIN) {
        fprintf(stderr, "Error: Integer overflow\n");
        return EXIT_FAILURE;
    }
    
    n = (int)val;
    
    long long result = hexagonal_number(n);
    
    if (result == -1) {
        fprintf(stderr, "Error: n must be positive\n");
        return EXIT_FAILURE;
    }
    
    printf("%lld\n", result);
    
    return EXIT_SUCCESS;
}