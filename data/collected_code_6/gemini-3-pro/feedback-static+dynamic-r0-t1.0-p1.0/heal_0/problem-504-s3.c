#include <stdio.h>
#include <stdlib.h>

unsigned long long calculate_cube_sum(int n) {
    if (n < 0 || n > 55108) {
        return 0;
    }
    
    unsigned long long un = (unsigned long long)n;
    unsigned long long base_sum = (un * (un + 1ULL)) / 2ULL;
    
    return base_sum * base_sum;
}

int main(void) {
    int n;
    
    if (scanf("%d", &n) != 1) {
        return EXIT_FAILURE;
    }
    
    if (n < 0 || n > 55108) {
        fprintf(stderr, "Input must be between 0 and 55108 to prevent overflow.\n");
        return EXIT_FAILURE;
    }
    
    unsigned long long result = calculate_cube_sum(n);
    printf("%llu\n", result);
    
    return EXIT_SUCCESS;
}