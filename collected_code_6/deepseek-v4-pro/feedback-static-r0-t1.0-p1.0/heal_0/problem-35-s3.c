#include <stdio.h>
#include <stdlib.h>

unsigned long long rectangular_number(int n) {
    if (n < 0) {
        fprintf(stderr, "Error: n must be non-negative\n");
        exit(EXIT_FAILURE);
    }
    return (unsigned long long)n * (n + 1);
}

int main(void) {
    int n;
    char input[32];
    
    printf("Enter n: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error: Failed to read input\n");
        return EXIT_FAILURE;
    }
    
    char *endptr;
    long val = strtol(input, &endptr, 10);
    
    if (endptr == input || *endptr != '\n' && *endptr != '\0') {
        fprintf(stderr, "Error: Invalid integer input\n");
        return EXIT_FAILURE;
    }
    
    if (val < 0 || val > 2147483647L) {
        fprintf(stderr, "Error: n out of range\n");
        return EXIT_FAILURE;
    }
    
    n = (int)val;
    
    unsigned long long result = rectangular_number(n);
    printf("The %d-th rectangular number is %llu\n", n, result);
    
    return EXIT_SUCCESS;
}