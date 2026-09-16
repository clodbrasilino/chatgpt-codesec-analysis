#include <stdio.h>
#include <stdint.h>

int find_most_significant_set_bit(uint32_t n) {
    if (n == 0) {
        return -1;
    }
    int msb = -1;
    while (n > 0) {
        n >>= 1;
        msb++;
    }
    return msb;
}

int main(void) {
    uint32_t num = 18;
    int msb_pos = find_most_significant_set_bit(num);
    
    if (msb_pos != -1) {
        printf("The position of the most significant set bit of %u is %d.\n", num, msb_pos);
    } else {
        printf("The number is 0, so it has no set bits.\n");
    }
    
    return 0;
}