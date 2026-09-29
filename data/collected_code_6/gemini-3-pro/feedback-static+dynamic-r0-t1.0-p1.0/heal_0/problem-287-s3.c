#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int calculate_even_squares_sum(uint32_t n, uint64_t *result) {
    if (n == 0 || result == NULL) {
        return -1;
    }

    uint64_t sum = 0;
    for (uint32_t i = 1; i <= n; ++i) {
        uint64_t even = (uint64_t)i * 2;
        uint64_t square = even * even;
        
        if (UINT64_MAX - sum < square) {
            return -1; 
        }
        sum += square;
    }

    *result = sum;
    return 0;
}

int main(void) {
    uint32_t n = 0;
    uint64_t result = 0;

    if (scanf("%u", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (calculate_even_squares_sum(n, &result) != 0) {
        fprintf(stderr, "Calculation failed due to invalid input or overflow\n");
        return EXIT_FAILURE;
    }

    printf("%llu\n", (unsigned long long)result);

    return EXIT_SUCCESS;
}