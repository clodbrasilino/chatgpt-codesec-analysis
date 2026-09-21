#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 4, got 7
  *  test case 2 failed: expected 17, got 28
  *  test case 0 failed: expected 1, got 2
  */

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
        
        /* Possible weaknesses found:
         * UBSan: division by zero (AFL crash: id:000000,sig:06,src:000000,time:132,execs:110,op:havoc,rep:11)
         */
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
    n = strtoull(buffer, &endptr, 10);
    
    if (errno != 0 || endptr == buffer) {
        return 1;
    }
    
    uint64_t result = count_unset_bits(n);
    printf("%" PRIu64 "\n", result);
    
    return 0;
}