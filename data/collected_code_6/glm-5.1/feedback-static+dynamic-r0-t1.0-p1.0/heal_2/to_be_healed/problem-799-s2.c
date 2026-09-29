#include <stdio.h>
#include <stdint.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 40, got <no output>
  *  test case 0 failed: expected 64, got <no output>
  *  test case 2 failed: expected 792, got <no output>
  */

uint32_t left_rotate_bits(uint32_t num, unsigned int d) {
    unsigned int shift = d % 32;
    if (shift == 0) {
        return num;
    }
    return (num << shift) | (num >> (32 - shift));
}

int main() {
    uint32_t num = 0x1A2B3C4D;
    unsigned int d = 8;
    
    uint32_t result = left_rotate_bits(num, d);
    
    printf("%u\n", result);
    
    return 0;
}