#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

long long sum_of_fourth_powers_of_odd_numbers(int n) {
    if (n <= 0) {
        return 0;
    }

    long long sum = 0;
    for (int i = 0; i < n; i++) {
        long long odd = 2 * i + 1;
        sum += odd * odd * odd * odd;
    }

    return sum;
}

int main(void) {
    int n;
    
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (n < 0) {
        fprintf(stderr, "Number must be non-negative\n");
        return EXIT_FAILURE;
    }

    long long result = sum_of_fourth_powers_of_odd_numbers(n);
    printf("%lld\n", result);

    return EXIT_SUCCESS;
}