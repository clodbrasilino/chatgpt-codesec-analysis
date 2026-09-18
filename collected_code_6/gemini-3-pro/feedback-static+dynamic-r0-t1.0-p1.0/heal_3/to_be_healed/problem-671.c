#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 15, got 31
  */

uint32_t set_rightmost_unset_bit(uint32_t n) {
    if (n == UINT32_MAX) {
        return n;
    }
    return n | (n + 1);
}

int main(void) {
    uint32_t num; 
    
    if (scanf("%u", &num) == 1) {
        uint32_t result = set_rightmost_unset_bit(num);
        printf("%u\n", result);
    }
    
    return EXIT_SUCCESS;
}