#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 40, got <no output>
  *  test case 0 failed: expected 64, got <no output>
  *  test case 2 failed: expected 792, got <no output>
  */

uint32_t left_rotate_bits(uint32_t num, uint32_t d) {
    uint32_t shift = d % 32;
    if (shift == 0) {
        return num;
    }
    return (num << shift) | (num >> (32 - shift));
}

int main(void) {
    const uint32_t arr[] = {0, 1, 2};
    const uint32_t shift_arr[] = {4, 8, 16};
    /* Possible weaknesses found:
     *  Variable 'expected' can be declared as const array [constVariable]
     */
    uint32_t expected[] = {64, 40, 792};
    
    for (int i = 0; i < 3; ++i) {
        uint32_t result = left_rotate_bits(arr[i], shift_arr[i]);
        if (result == expected[i]) {
            printf("%" PRIu32 "\n", result);
        }
    }
    
    return 0;
}