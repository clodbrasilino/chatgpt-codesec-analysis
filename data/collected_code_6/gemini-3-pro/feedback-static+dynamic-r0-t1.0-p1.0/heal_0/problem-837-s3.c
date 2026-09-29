#include <stdio.h>
#include <stdlib.h>

unsigned long long cube_sum_odd_numbers(int n) {
    if (n <= 0) {
        return 0;
    }
    
    unsigned long long n_ull = (unsigned long long)n;
    unsigned long long sum = n_ull * n_ull * ((2ULL * n_ull * n_ull) - 1ULL);
    
    return sum;
}

int main(void) {
    int n;
    
    if (scanf("%d", &n) != 1) {
        return EXIT_FAILURE;
    }
    
    if (n < 0) {
        return EXIT_FAILURE;
    }
    
    unsigned long long result = cube_sum_odd_numbers(n);
    printf("%llu\n", result);
    
    return EXIT_SUCCESS;
}