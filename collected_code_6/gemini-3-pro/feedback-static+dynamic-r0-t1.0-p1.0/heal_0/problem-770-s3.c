#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint64_t sum_of_fourth_powers_of_odd_numbers(uint32_t n) {
    uint64_t sum = 0;
    for (uint32_t i = 1; i <= n; ++i) {
        uint64_t odd = 2ULL * i - 1ULL;
        uint64_t power = odd * odd * odd * odd;
        sum += power;
    }
    return sum;
}

int main(void) {
    uint32_t n;
    
    if (scanf("%u", &n) != 1) {
        fprintf(stderr, "Error: Invalid input.\n");
        return EXIT_FAILURE;
    }

    uint64_t result = sum_of_fourth_powers_of_odd_numbers(n);
    printf("%lu\n", (unsigned long)result);

    return EXIT_SUCCESS;
}