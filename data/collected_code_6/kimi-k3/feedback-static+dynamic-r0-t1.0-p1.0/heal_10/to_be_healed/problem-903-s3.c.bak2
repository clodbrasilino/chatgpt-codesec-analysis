#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 4, got <no output>
  *  test case 2 failed: expected 17, got <no output>
  *  test case 0 failed: expected 1, got <no output>
  */

static uint64_t count_unset_bits(uint64_t n)
{
    uint64_t total_unset = 0;
    uint64_t power_of_2 = 1;
    unsigned int bit_position = 0;

    while (bit_position < 64) {
        uint64_t divisor = power_of_2 << 1;
        uint64_t complete_cycles = (n + 1) / divisor;
        uint64_t remainder = (n + 1) % divisor;
        
        uint64_t zeros_in_column = complete_cycles * power_of_2;
        if (remainder > power_of_2) {
            zeros_in_column += remainder - power_of_2;
        }
        
        total_unset += zeros_in_column;
        
        if (bit_position == 63) {
            break;
        }
        power_of_2 <<= 1;
        bit_position++;
    }

    return total_unset;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000000,time:254,execs:236,op:havoc,rep:8; likely memory-safety defect
  */

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