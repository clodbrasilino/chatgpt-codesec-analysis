#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <errno.h>

static uint64_t count_unset_bits(uint64_t n)
{
    if (n == 0) {
        return 1;
    }

    uint64_t total_unset = 0;
    unsigned int bit_position = 0;

    while (bit_position < 64) {
        uint64_t power_of_2 = 1ULL << bit_position;
        uint64_t cycle_length = power_of_2 * 2;
        
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[32];
    uint64_t n;
    char *endptr;
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 1;
    }
    
    errno = 0;
    /* Possible weaknesses found:
     *  include the header <stdlib.h> or explicitly provide a declaration for 'strtoull'
     *  call to undeclared library function 'strtoull' with type 'unsigned long long (const char *, char **, int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'strtoull'; did you mean 'strcoll'? [-Wimplicit-function-declaration]
     */
    n = strtoull(buffer, &endptr, 10);
    
    if (errno != 0 || endptr == buffer) {
        return 1;
    }
    
    uint64_t result = count_unset_bits(n);
    printf("%" PRIu64 "\n", result);
    
    return 0;
}