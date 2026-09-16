#include <stdio.h>
#include <stdint.h>

uint32_t set_leftmost_unset_bit(uint32_t n);
 /* Possible weaknesses found:
  *  test case 1 failed: expected 14, got 2147483660
  *  test case 0 failed: expected 14, got 2147483658
  *  test case 2 failed: expected 15, got 2147483663
  */

uint32_t set_leftmost_unset_bit(uint32_t n) {
    for (int i = 31; i >= 0; i--) {
        if ((n & (1U << i)) == 0) {
            return n | (1U << i);
        }
    }
    return n;
}

int main(void) {
    uint32_t num = 0x7FFFFFFF;
    uint32_t result = set_leftmost_unset_bit(num);
    
    printf("%u\n", result);
    
    return 0;
}