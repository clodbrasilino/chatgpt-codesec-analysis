#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint64_t get_nth_tetrahedral_number(uint32_t n) {
    uint64_t n_u64 = (uint64_t)n;
    return (n_u64 * (n_u64 + 1) * (n_u64 + 2)) / 6;
}

int main(void) {
    uint32_t n;
    
    if (scanf("%u", &n) != 1) {
        return EXIT_FAILURE;
    }
    
    uint64_t result = get_nth_tetrahedral_number(n);
    printf("%llu\n", (unsigned long long)result);
    
    return EXIT_SUCCESS;
}