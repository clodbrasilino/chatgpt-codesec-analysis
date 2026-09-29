#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>
#include <errno.h>
#include <string.h>

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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    uint64_t n;
    char *endptr;
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 1;
    }
    
    buffer[sizeof(buffer) - 1] = '\0';
    
    errno = 0;
    n = strtoull(buffer, &endptr, 10);
    
    if (errno != 0 || endptr == buffer || (*endptr != '\n' && *endptr != '\0')) {
        return 1;
    }
    
    uint64_t result = count_unset_bits(n);
    printf("%" PRIu64 "\n", result);
    
    return 0;
}