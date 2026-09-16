#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint64_t count_total_unset_bits(uint64_t n) {
    if (n == 0) {
        return 1;
    }

    uint64_t total_bits = 0;
    uint64_t temp = n;
    while (temp > 0) {
        total_bits++;
        temp >>= 1;
    }

    uint64_t total_set_bits = 0;
    for (uint64_t i = 1; i <= n; i++) {
        uint64_t current = i;
        while (current > 0) {
            total_set_bits += (current & 1);
            current >>= 1;
        }
    }

    uint64_t total_possible_bits = 0;
    for (uint64_t i = 1; i <= n; i++) {
        uint64_t temp_i = i;
        uint64_t num_bits = 0;
        while (temp_i > 0) {
            num_bits++;
            temp_i >>= 1;
        }
        total_possible_bits += num_bits;
    }

    return total_possible_bits - total_set_bits;
}

int main(void) {
    uint64_t n = 0;
    
    if (scanf("%lu", &n) != 1) {
        return EXIT_FAILURE;
    }

    uint64_t unset_bits = count_total_unset_bits(n);
    printf("%lu\n", unset_bits);

    return EXIT_SUCCESS;
}