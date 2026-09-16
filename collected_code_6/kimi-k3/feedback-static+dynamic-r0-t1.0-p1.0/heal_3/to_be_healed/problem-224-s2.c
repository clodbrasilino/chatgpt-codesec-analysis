#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 2, got <no output>
  *  test case 0 failed: expected 1, got <no output>
  *  test case 1 failed: expected 1, got <no output>
  */

unsigned int count_set_bits(uint32_t number) {
    unsigned int count = 0;
    while (number != 0) {
        number &= (number - 1);
        count++;
    }
    return count;
}

int main(void) {
    uint32_t input;
    int scan_result;
    
    scan_result = scanf("%" SCNu32, &input);
    
    if (scan_result != 1) {
        return 1;
    }
    
    printf("%u\n", count_set_bits(input));
    
    return 0;
}