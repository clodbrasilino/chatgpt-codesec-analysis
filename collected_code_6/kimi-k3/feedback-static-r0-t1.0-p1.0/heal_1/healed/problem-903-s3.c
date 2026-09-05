#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>

static uint64_t count_unset_bits(uint64_t n)
{
    if (n == 0) {
        return 0;
    }

    uint64_t total_unset = 0;
    uint64_t power_of_2 = 1;
    unsigned int bit_position = 0;

    while (power_of_2 <= n) {
        uint64_t complete_cycles = (n + 1) / (power_of_2 * 2);
        uint64_t remainder = (n + 1) % (power_of_2 * 2);
        
        uint64_t zeros_in_column = complete_cycles * power_of_2;
        if (remainder > power_of_2) {
            zeros_in_column += remainder - power_of_2;
        }
        
        total_unset += zeros_in_column;
        
        if (power_of_2 > UINT64_MAX / 2) {
            break;
        }
        power_of_2 *= 2;
        bit_position++;
        
        if (bit_position >= 64) {
            break;
        }
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