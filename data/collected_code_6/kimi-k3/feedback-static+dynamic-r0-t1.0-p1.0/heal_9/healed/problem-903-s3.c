#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

static uint64_t count_unset_bits(uint64_t n)
{
    uint64_t total_unset = 0;
    unsigned int bit_position = 0;

    while (bit_position < 64) {
        uint64_t power_of_2 = 1ULL << bit_position;
        uint64_t cycle_length = power_of_2 * 2;
        
        if (cycle_length == 0) {
            break;
        }
        
        uint64_t complete_cycles = (n + 1) / cycle_length;
        uint64_t remainder = (n + 1) % cycle_length;
        
        uint64_t zeros_in_column = complete_cycles * power_of_2;
        if (remainder > power_of_2) {
            zeros_in_column += remainder - power_of_2;
        }
        
        total_unset += zeros_in_column;
        bit_position++;
    }

    return total_unset;
}

int main(void)
{
    char buffer[128];
    uint64_t n;
    char *endptr;
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 1;
    }
    
    errno = 0;
    n = strtoull(buffer, &endptr, 10);
    
    if (errno != 0 || endptr == buffer) {
        return 1;
    }
    
    uint64_t result = count_unset_bits(n);
    printf("%" PRIu64 "\n", result);
    
    return 0;
}