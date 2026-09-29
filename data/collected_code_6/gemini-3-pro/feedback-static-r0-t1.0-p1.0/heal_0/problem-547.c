#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

uint64_t calculate_consecutive_hamming_sum(uint32_t n);

uint64_t calculate_consecutive_hamming_sum(uint32_t n) {
    uint64_t total_distance = 0;
    while (n > 0) {
        total_distance += n;
        n >>= 1;
    }
    return total_distance;
}

int main(void) {
    uint32_t n = 0;
    
    if (scanf("%u", &n) != 1) {
        return EXIT_FAILURE;
    }

    uint64_t result = calculate_consecutive_hamming_sum(n);
    
    if (printf("%llu\n", (unsigned long long)result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}