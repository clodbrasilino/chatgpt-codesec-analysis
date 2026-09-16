#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

int first_digit_factorial(int n) {
    if (n < 0) {
        return -1;
    }
    if (n <= 1) {
        return 1;
    }
    
    double log_sum = 0.0;
    for (int i = 1; i <= n; i++) {
        log_sum += log10(i);
    }
    
    double fractional_part = log_sum - floor(log_sum);
    double first_d = pow(10.0, fractional_part);
    
    return (int)floor(first_d);
}

int main(int argc, char const * const argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    
    long val = strtol(argv[1], NULL, 10);
    if (val < 0 || val > INT_MAX) {
        return EXIT_FAILURE;
    }
    
    int result = first_digit_factorial((int)val);
    if (result == -1) {
        return EXIT_FAILURE;
    }
    
    printf("%d\n", result);
    return EXIT_SUCCESS;
}