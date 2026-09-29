#include <stdio.h>
#include <stdlib.h>

unsigned long long calculate_cube_sum(unsigned int n) {
    unsigned long long sum = 0;
    for (unsigned int i = 1; i <= n; i++) {
        unsigned long long term = (unsigned long long)i * i * i;
        if (sum > __LONG_LONG_MAX__ - term) {
            fprintf(stderr, "Error: Integer overflow detected.\n");
            exit(EXIT_FAILURE);
        }
        sum += term;
    }
    return sum;
}

int main(void) {
    int input = 0;
    unsigned int n = 0;
    
    if (printf("Enter a positive integer: ") < 0) {
        return EXIT_FAILURE;
    }
    
    if (scanf("%d", &input) != 1) {
        fprintf(stderr, "Error: Invalid input.\n");
        return EXIT_FAILURE;
    }
    
    if (input < 1) {
        fprintf(stderr, "Error: Number must be positive.\n");
        return EXIT_FAILURE;
    }
    
    n = (unsigned int)input;
    
    unsigned long long result = calculate_cube_sum(n);
    
    if (printf("Sum of the series is: %llu\n", result) < 0) {
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}