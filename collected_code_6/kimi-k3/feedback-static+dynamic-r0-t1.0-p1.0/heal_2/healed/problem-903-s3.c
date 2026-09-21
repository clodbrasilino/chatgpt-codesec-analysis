#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

static uint64_t count_unset_bits(uint64_t n)
{
    if (n == 0) {
        return 1;
    }

    uint64_t total_unset = 0;
    unsigned int bit_position = 0;

    while (bit_position < 64) {
        uint64_t power_of_2 = (bit_position == 63) ? 0x8000000000000000ULL : (1ULL << bit_position);
        uint64_t cycle_length = (bit_position == 63) ? 0 : (power_of_2 * 2);
        
        if (bit_position < 63) {
            uint64_t complete_cycles = (n + 1) / cycle_length;
            uint64_t remainder = (n + 1) % cycle_length;
            
            uint64_t zeros_in_column = complete_cycles * power_of_2;
            if (remainder > power_of_2) {
                zeros_in_column += remainder - power_of_2;
            }
            
            total_unset += zeros_in_column;
        } else {
            if (n < power_of_2) {
                total_unset += 1;
            }
        }
        
        bit_position++;
    }

    return total_unset;
}

int main(void)
{
    uint64_t n;
    
    if (scanf("%" SCNu64, &n) != 1) {
        return 1;
    }
    
    uint64_t result = count_unset_bits(n);
    printf("%" PRIu64 "\n", result);
    
    return 0;
}