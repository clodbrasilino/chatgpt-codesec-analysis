#include <stdio.h>
#include <stdlib.h>

unsigned long long countTotalSetBits(unsigned long long n) {
    unsigned long long count = 0;
    
    for (unsigned long long i = 0; (1ULL << i) <= n; i++) {
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
 /* Possible weaknesses found:
  *  test case 1 failed: expected 4, got 11
  *  test case 0 failed: expected 1, got 4
  *  test case 2 failed: expected 17, got 32
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
    unsigned long long set_bits = countTotalSetBits(n);
    
    return total_positions - set_bits;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000002,time:176,execs:136,op:havoc,rep:9; likely memory-safety defect
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