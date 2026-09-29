#include <stdio.h>
#include <stdint.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 64, got <no output>
  *  test case 2 failed: expected 792, got <no output>
  *  test case 1 failed: expected 40, got <no output>
  */

uint32_t left_rotate(uint32_t num, unsigned int n) {
    n %= 32;
    if (n == 0) {
        return num;
    }
    return (num << n) | (num >> (32 - n));
}

int main(void) {
    uint32_t num = 0x12345678;
    unsigned int rotate_by = 4;
    uint32_t result = left_rotate(num, rotate_by);
    printf("Original: 0x%08X\n", num);
    printf("Rotated left by %u: 0x%08X\n", rotate_by, result);
    return 0;
}