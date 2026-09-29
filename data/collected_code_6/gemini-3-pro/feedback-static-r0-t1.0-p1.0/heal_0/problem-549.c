#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint64_t sum_of_fifth_power_of_odd_numbers(int n) {
    if (n < 0) {
        return 0;
    }

    uint64_t sum = 0;
    uint64_t current_odd = 1;

    for (int i = 0; i < n; i++) {
        uint64_t power = current_odd * current_odd * current_odd * current_odd * current_odd;
        
        if (UINT64_MAX - sum < power) {
            fprintf(stderr, "Integer overflow occurred.\n");
            exit(EXIT_FAILURE);
        }
        
        sum += power;
        current_odd += 2;
    }

    return sum;
}

int main(void) {
    int n;

    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    if (n < 0) {
        fprintf(stderr, "Input must be a non-negative integer.\n");
        return EXIT_FAILURE;
    }

    uint64_t result = sum_of_fifth_power_of_odd_numbers(n);
    printf("%llu\n", (unsigned long long)result);

    return EXIT_SUCCESS;
}