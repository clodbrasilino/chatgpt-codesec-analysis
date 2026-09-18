#include <stdio.h>
#include <stdlib.h>

long long calculate_difference(long long n) {
    if (n < 0) {
        return -1;
    }

    unsigned long long un = (unsigned long long)n;
    unsigned long long sum_of_n = (un * (un + 1)) / 2;
    unsigned long long squared_sum = sum_of_n * sum_of_n;
    unsigned long long sum_of_squares = (un * (un + 1) * (2 * un + 1)) / 6;

    return (long long)(squared_sum - sum_of_squares);
}

int main(void) {
    long long n;
    
    if (scanf("%lld", &n) != 1) {
        return EXIT_FAILURE;
    }

    if (n < 0) {
        return EXIT_FAILURE;
    }

    long long difference = calculate_difference(n);
    if (difference < 0 && n != 0) {
        return EXIT_FAILURE;
    }
    
    printf("%lld\n", difference);

    return EXIT_SUCCESS;
}