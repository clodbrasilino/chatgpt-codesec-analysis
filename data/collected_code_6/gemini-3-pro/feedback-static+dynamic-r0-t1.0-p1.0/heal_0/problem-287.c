#include <stdio.h>
#include <stdlib.h>

unsigned long long calculate_sum_of_even_squares(unsigned int n) {
    unsigned long long n_ull = (unsigned long long)n;
    return (2ULL * n_ull * (n_ull + 1ULL) * (2ULL * n_ull + 1ULL)) / 3ULL;
}

int main(void) {
    unsigned int n = 0;
    
    if (scanf("%u", &n) != 1) {
        return EXIT_FAILURE;
    }

    if (n > 2000000U) {
        return EXIT_FAILURE;
    }

    printf("%llu\n", calculate_sum_of_even_squares(n));

    return EXIT_SUCCESS;
}