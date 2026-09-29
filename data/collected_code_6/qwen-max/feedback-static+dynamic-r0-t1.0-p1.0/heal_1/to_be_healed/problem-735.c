#include <stdio.h>
#include <stdint.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 12, got 9
  *  test case 2 failed: expected 13, got 8
  *  test case 0 failed: expected 15, got 10
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
    uint32_t mask = (1 << (len - 2)) - 1;
    return num ^ mask;
}

int main() {
    uint32_t num = 0b10101010101010101010101010101010;
    num = toggle_middle_bits(num);
    printf("%u\n", num);
    return 0;
}