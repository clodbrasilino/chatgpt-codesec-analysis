#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

int first_factorial_digit(int n) {
    if (n < 0) {
        exit(EXIT_FAILURE);
    }
    if (n == 0) {
        return 1;
    }
    long double log_sum = 0.0L;
    for (int i = 1; i <= n; i++) {
        log_sum += log10l(i);
    }
    long double fractional = log_sum - floorl(log_sum);
    long double first = powl(10.0L, fractional);
    return (int)first;
}

int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    long val = strtol(argv[1], NULL, 10);
    if (val < 0 || val > INT_MAX) {
        return EXIT_FAILURE;
    }
    int result = first_factorial_digit((int)val);
    printf("%d\n", result);
    return EXIT_SUCCESS;
}