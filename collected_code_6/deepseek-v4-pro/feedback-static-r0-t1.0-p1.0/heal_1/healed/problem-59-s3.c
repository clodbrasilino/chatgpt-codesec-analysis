#include <stdio.h>
#include <stdlib.h>

long long octagonal_number(int n) {
    if (n <= 0) {
        return -1;
    }
    return (long long)n * (3 * n - 2);
}

int main(int argc, char *const argv[]) {
    int n;
    
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    
    if (*endptr != '\0' || val <= 0 || val > 2147483647) {
        fprintf(stderr, "Error: Invalid input. Please provide a positive integer.\n");
        return EXIT_FAILURE;
    }
    
    n = (int)val;
    
    long long result = octagonal_number(n);
    
    if (result < 0) {
        fprintf(stderr, "Error: Input must be positive.\n");
        return EXIT_FAILURE;
    }
    
    printf("%lld\n", result);
    
    return EXIT_SUCCESS;
}