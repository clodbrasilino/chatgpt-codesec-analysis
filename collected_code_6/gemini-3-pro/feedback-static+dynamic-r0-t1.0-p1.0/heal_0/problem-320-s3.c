#include <stdio.h>
#include <stdlib.h>

long long calculate_difference(long long n) {
    if (n < 0) {
        return -1;
    }

    long long sum_of_n = (n * (n + 1)) / 2;
    long long squared_sum = sum_of_n * sum_of_n;

    long long sum_of_squares = (n * (n + 1) * (2 * n + 1)) / 6;

    return squared_sum - sum_of_squares;
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