#include <stdio.h>
#include <stdlib.h>

unsigned long long get_nth_hexagonal_number(unsigned int n) {
    if (n == 0) {
        return 0;
    }
    
    if (n > 3000000000U) {
        return 0;
    }
    
    return (unsigned long long)n * (2ULL * n - 1ULL);
}

int main(void) {
    unsigned int n = 10;
    unsigned long long result = get_nth_hexagonal_number(n);
    
    if (result == 0 && n != 0) {
        fprintf(stderr, "Error: Integer overflow or invalid input.\n");
        return EXIT_FAILURE;
    }
    
    printf("%llu\n", result);
    
    return EXIT_SUCCESS;
}