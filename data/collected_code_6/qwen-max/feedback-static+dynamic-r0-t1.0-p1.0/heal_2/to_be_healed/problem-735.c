#include <stdio.h>
#include <stdint.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 12, got <no output>
  *  test case 2 failed: expected 13, got <no output>
  *  test case 0 failed: expected 15, got <no output>
  */

uint32_t toggle_middle_bits(uint32_t num) {
    uint32_t len = 0;
    uint32_t n = num;
    while (n > 0) {
        len++;
        n >>= 1;
    }
    if (len <= 2) {
        return num;
    }
    uint32_t mask = (1 << (len - 1)) - 1;
    mask &= ~(1 | (1 << (len - 1)));
    return num ^ mask;
}

int main() {
    uint32_t num = 0b10101010101010101010101010101010;
    num = toggle_middle_bits(num);
    printf("%u\n", num);
    return 0;
}