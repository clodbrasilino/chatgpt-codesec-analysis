#include <stdio.h>
#include <stdlib.h>

unsigned long long countTotalSetBits(unsigned long long n) {
    unsigned long long count = 0;
    
    for (unsigned long long bit_mask = 1; bit_mask > 0; bit_mask <<= 1) {
        unsigned long long period = bit_mask << 1;
        
        if (period == 0) {
            break;
        }
        
        unsigned long long complete_pairs = (n + 1) / period;
        count += complete_pairs * bit_mask;
        
        unsigned long long remainder = (n + 1) % period;
        if (remainder > bit_mask) {
            count += remainder - bit_mask;
        }
    }
    
    return count;
}

unsigned long long countTotalSetBitsInMSB(unsigned long long n) {
    unsigned long long msb = 0;
    unsigned long long temp = n;
    while (temp > 0) {
        msb++;
        temp >>= 1;
    }
    if (msb == 0) return 0;
    
    unsigned long long msb_value = 1ULL << (msb - 1);
    unsigned long long count = 0;
    
    for (unsigned long long bit_mask = 1; bit_mask > 0 && bit_mask <= msb_value; bit_mask <<= 1) {
        unsigned long long period = bit_mask << 1;
        unsigned long long complete_pairs = (n + 1) / period;
        count += complete_pairs * bit_mask;
        
        unsigned long long remainder = (n + 1) % period;
        if (remainder > bit_mask) {
            count += remainder - bit_mask;
        }
    }
    
    return count;
}
 /* Possible weaknesses found:
  *  test case 2 failed: expected 17, got 44
  *  test case 0 failed: expected 1, got 5
  *  test case 1 failed: expected 4, got 15
  */

unsigned long long countTotalUnsetBits(unsigned long long n) {
    if (n == 0) return 0;
    
    unsigned long long total_bits = 0;
    unsigned long long temp = n;
    
    while (temp > 0) {
        total_bits++;
        temp >>= 1;
    }
    
    unsigned long long total_positions = total_bits * (n + 1);
    
    /* Possible weaknesses found:
     *  Value stored to 'set_bits' during its initialization is never read [deadcode.DeadStores]
     *  set_bits is initialized
     */
    unsigned long long set_bits = countTotalSetBitsInMSB(n);
    
    unsigned long long highest_bit_mask = 1ULL << (total_bits - 1);
    unsigned long long below_msb = n & (highest_bit_mask - 1);
    unsigned long long msb_set_bits = n - highest_bit_mask + 1;
    
    /* Possible weaknesses found:
     *  Redundant initialization for 'set_bits'. The initialized value is overwritten before it is read. [redundantInitialization]
     *  set_bits is overwritten
     */
    set_bits = msb_set_bits + countTotalSetBits(below_msb);
    
    return total_positions - set_bits;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:327,execs:339,op:havoc,rep:4; likely memory-safety defect
  */

int main(void) {
    unsigned long long n;
    
    printf("Enter a number: ");
    if (scanf("%llu", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    unsigned long long result = countTotalUnsetBits(n);
    printf("Total unset bits from 1 to %llu: %llu\n", n, result);
    
    return EXIT_SUCCESS;
}