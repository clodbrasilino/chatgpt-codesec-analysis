#include <stdio.h>
#include <stdlib.h>

long long calculate_difference(long long n) {
    if (n < 0 || n > 77934) {
        return -1; 
    }
    
    long long sum_of_squares = (n * (n + 1) * (2 * n + 1)) / 6;
    long long sum = (n * (n + 1)) / 2;
    long long square_of_sum = sum * sum;
    
    return square_of_sum - sum_of_squares;
}

int main(void) {
    long long n;
    long long result;

    if (scanf("%lld", &n) != 1) {
        return EXIT_FAILURE;
    }

    result = calculate_difference(n);
    if (result == -1) {
        return EXIT_FAILURE;
    }

    printf("%lld\n", result);

    return EXIT_SUCCESS;
}