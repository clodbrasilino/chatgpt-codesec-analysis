#include <stdio.h>
#include <stdlib.h>

unsigned long long sum_even_index_binomial_coeffs(unsigned int n) {
    if (n == 0) {
        return 1;
    }
    return 1ULL << (n - 1);
}

int main(void) {
    unsigned int n = 0;
    
    if (scanf("%u", &n) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    if (n > 63) {
        fprintf(stderr, "Input too large, would overflow.\n");
        return EXIT_FAILURE;
    }

    unsigned long long result = sum_even_index_binomial_coeffs(n);
    printf("%llu\n", result);

    return EXIT_SUCCESS;
}