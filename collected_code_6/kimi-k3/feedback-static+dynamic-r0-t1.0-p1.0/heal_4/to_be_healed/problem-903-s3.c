#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 17, got <no output>
  *  test case 0 failed: expected 1, got <no output>
  *  test case 1 failed: expected 4, got <no output>
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
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000000,time:633,execs:251,op:havoc,rep:3; likely memory-safety defect
  */

int main(void)
{
    uint64_t n;
    
    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNu64, &n) != 1) {
        return 1;
    }
    
    uint64_t result = count_unset_bits(n);
    printf("%" PRIu64 "\n", result);
    
    return 0;
}