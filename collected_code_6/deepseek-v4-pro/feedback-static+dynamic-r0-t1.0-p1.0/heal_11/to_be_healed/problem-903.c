#include <stdio.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 1, got 4
  *  test case 2 failed: expected 17, got 32
  *  test case 1 failed: expected 4, got 11
  */

unsigned long long count_total_unset_bits(unsigned long long n) {
    if (n == 0) return 1;
    
    unsigned long long total_bits = 0;
    unsigned long long temp = n;
    while (temp > 0) {
        total_bits++;
        temp >>= 1;
    }
    
    unsigned long long total_set_bits = 0;
    
    for (unsigned long long i = 0; i < total_bits; i++) {
        unsigned long long bit_mask = 1ULL << i;
        /* Possible weaknesses found:
         * UBSan: division by zero (AFL crash: id:000000,sig:06,src:000002,time:307,execs:262,op:havoc,rep:13)
         */
        unsigned long long pairs = (n + 1) / (bit_mask << 1);
        
        total_set_bits += pairs * bit_mask;
        
        unsigned long long remainder = (n + 1) % (bit_mask << 1);
        if (remainder > bit_mask) {
            total_set_bits += remainder - bit_mask;
        }
    }
    
    unsigned long long total_positions = n + 1;
    return total_positions * total_bits - total_set_bits;
}

int main(void) {
    unsigned long long n;
    
    printf("Enter a number: ");
    if (scanf("%llu", &n) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    
    unsigned long long result = count_total_unset_bits(n);
    printf("%llu\n", result);
    
    return 0;
}