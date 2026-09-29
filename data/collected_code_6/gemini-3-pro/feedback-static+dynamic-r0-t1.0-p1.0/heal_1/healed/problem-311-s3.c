#include <stdio.h>
#include <limits.h>

unsigned int set_leftmost_unset_bit(unsigned int n) {
    int i;
    int total_bits = sizeof(n) * CHAR_BIT;
    int msb = -1;
    
    for (i = total_bits - 1; i >= 0; i--) {
        if (n & (1U << i)) {
            msb = i;
            break;
        }
    }
    
    if (msb == -1) {
        return 0;
    }
    
    for (i = msb - 1; i >= 0; i--) {
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