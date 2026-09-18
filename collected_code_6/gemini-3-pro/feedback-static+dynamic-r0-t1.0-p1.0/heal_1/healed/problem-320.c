#include <stdio.h>
#include <stdlib.h>

long long calculate_difference(long long n) {
    if (n < 0) {
        return -1;
    }

    unsigned __int128 un = (unsigned __int128)n;
    
    unsigned __int128 sum = (un * (un + 1)) / 2;
    unsigned __int128 squared_sum = sum * sum;
    
    unsigned __int128 sum_of_squares = (un * (un + 1) * (2 * un + 1)) / 6;

    return (long long)(squared_sum - sum_of_squares);
}

int main(void) {
    long long n;
    
    if (scanf("%lld", &n) != 1) {
        return EXIT_FAILURE;
    }

    long long result = calculate_difference(n);
    if (result == -1) {
        return EXIT_FAILURE;
    }

    printf("%lld\n", result);

    return EXIT_SUCCESS;
}