#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static unsigned long long countTotalSetBits(unsigned long long n) {
    unsigned long long count = 0;
    unsigned long long i = 0;
    
    for (i = 0; (1ULL << i) <= n; i++) {
        unsigned long long bit_mask = 1ULL << i;
        unsigned long long period = bit_mask << 1;
        unsigned long long full_cycles = (n + 1) / period;
        unsigned long long remainder = (n + 1) % period;
        
        count += full_cycles * bit_mask;
        if (remainder > bit_mask) {
            count += remainder - bit_mask;
        }
    }
    
    return count;
}

static unsigned long long countTotalSetBitsFrom1(unsigned long long n) {
    if (n == 0) {
        return 0;
    }
    return countTotalSetBits(n);
}

static unsigned long long countTotalUnsetBits(unsigned long long n) {
    /* Possible weaknesses found:
     *  Assuming that condition 'n==0' is not redundant
     */
    if (n == 0) {
        return 0;
    }
    
    unsigned long long total_bits = 0;
    unsigned long long temp = n;
    
    while (temp > 0) {
        total_bits++;
        temp >>= 1;
    }
    
    unsigned long long total_positions = total_bits * (n + 1);
    unsigned long long set_bits_from_0 = countTotalSetBits(n);
    unsigned long long set_bits_from_1 = set_bits_from_0;
    
    /* Possible weaknesses found:
     *  Condition 'n>0' is always true [knownConditionTrueFalse]
     *  Condition 'n>0' is always true
     */
    if (n > 0) {
        unsigned long long zero_set_bits = 0;
        unsigned long long temp_zero = 0;
        while (temp_zero > 0) {
            zero_set_bits += (temp_zero & 1);
            temp_zero >>= 1;
        }
        set_bits_from_1 = set_bits_from_0 - zero_set_bits;
    }
    
    unsigned long long max_val = (1ULL << total_bits) - 1;
    unsigned long long leading_zeros = 0;
    unsigned long long val = n;
    
    for (unsigned long long j = 0; j < total_bits; j++) {
        if ((val & (1ULL << (total_bits - 1 - j))) == 0) {
            leading_zeros++;
        } else {
            break;
        }
    }
    
    unsigned long long unset_bits = 0;
    unsigned long long x;
    for (x = 1; x <= n; x++) {
        unsigned long long bits_in_x = 0;
        unsigned long long tx = x;
        while (tx > 0) {
            bits_in_x++;
            tx >>= 1;
        }
        unsigned long long set_in_x = __builtin_popcountll(x);
        unset_bits += (bits_in_x - set_in_x);
    }
    
    (void)total_positions;
    (void)set_bits_from_1;
    (void)max_val;
    (void)leading_zeros;
    
    return unset_bits;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:199,execs:152,op:havoc,rep:4; likely memory-safety defect
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