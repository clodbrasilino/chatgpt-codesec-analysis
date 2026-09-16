#include <stdio.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 14, got 2147483660
  *  test case 0 failed: expected 14, got 2147483658
  *  test case 2 failed: expected 15, got 2147483663
  */

unsigned int set_leftmost_unset_bit(unsigned int n) {
    int i;
    int total_bits = sizeof(n) * CHAR_BIT;
    
    for (i = total_bits - 1; i >= 0; i--) {
        if ((n & (1U << i)) == 0) {
            n |= (1U << i);
            break;
        }
    }
    
    return n;
}

int main(void) {
    unsigned int num = 21; 
    unsigned int result = set_leftmost_unset_bit(num);
    
    printf("%u\n", result);
    
    return 0;
}