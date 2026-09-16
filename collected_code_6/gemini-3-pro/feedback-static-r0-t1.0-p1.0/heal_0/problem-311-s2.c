#include <stdio.h>
#include <stdint.h>

uint32_t set_leftmost_unset_bit(uint32_t n);

uint32_t set_leftmost_unset_bit(uint32_t n) {
    for (int i = 31; i >= 0; i--) {
        if ((n & (1U << i)) == 0) {
            return n | (1U << i);
        }
    }
    return n;
}

int main(void) {
    uint32_t num = 0x7FFFFFFF;
    uint32_t result = set_leftmost_unset_bit(num);
    
    printf("%u\n", result);
    
    return 0;
}