#include <stdio.h>
#include <stdint.h>

uint32_t set_leftmost_unset_bit(uint32_t n) {
    if (n == 0) {
        return 1;
    }
    
    int msb = 31;
    while ((n & (1U << msb)) == 0 && msb > 0) {
        msb--;
    }
    
    for (int i = msb - 1; i >= 0; i--) {
        if ((n & (1U << i)) == 0) {
            return n | (1U << i);
        }
    }
    
    if (msb < 31) {
        return n | (1U << (msb + 1));
    }
    
    return n;
}

int main(void) {
    uint32_t test_val1 = 12;
    uint32_t test_val2 = 10;
    uint32_t test_val3 = 7;
    
    uint32_t res1 = set_leftmost_unset_bit(test_val1);
    uint32_t res2 = set_leftmost_unset_bit(test_val2);
    uint32_t res3 = set_leftmost_unset_bit(test_val3);

    printf("%u\n", res1);
    printf("%u\n", res2);
    printf("%u\n", res3);

    return 0;
}