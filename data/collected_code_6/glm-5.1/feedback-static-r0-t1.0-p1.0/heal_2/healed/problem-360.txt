#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>

uint64_t carol_number(int n) {
    if (n < 1) {
        exit(EXIT_FAILURE);
    }
    
    int shift = n + 1;
    
    if (shift >= 64) {
        exit(EXIT_FAILURE);
    }
    
    uint64_t power_of_two = (uint64_t)1 << shift;
    uint64_t two_n_minus_one = power_of_two - 1;
    uint64_t result = two_n_minus_one * two_n_minus_one - 2;
    
    return result;
}

int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    long n = strtol(argv[1], NULL, 10);
    
    if (n < 1 || n > INT_MAX) {
        fprintf(stderr, "n must be a positive integer\n");
        return EXIT_FAILURE;
    }
    
    uint64_t res = carol_number((int)n);
    printf("%llu\n", (unsigned long long)res);
    
    return EXIT_SUCCESS;
}