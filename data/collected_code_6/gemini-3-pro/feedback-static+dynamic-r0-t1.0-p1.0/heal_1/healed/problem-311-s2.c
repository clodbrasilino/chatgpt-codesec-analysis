#include <stdio.h>
#include <stdint.h>

uint32_t set_leftmost_unset_bit(uint32_t n);

uint32_t set_leftmost_unset_bit(uint32_t n) {
    if (n == 0) {
        return 0;
    }
    
    int msb = 31;
    while (msb >= 0 && (n & (1U << msb)) == 0) {
        msb--;
    }
    
    for (int i = msb - 1; i >= 0; i--) {
        if ((n & (1U << i)) == 0) {
            return n | (1U << i);
        }
    }
    
    return n;
}

int main(void) {
    uint32_t num = 10;
    uint32_t result = set_leftmost_unset_bit(num);
    
    printf("%u\n", result);
    
    return 0;
}