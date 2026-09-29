#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

unsigned int toggle_middle_bits(unsigned int n) {
    if (n == 0) {
        return 0;
    }
    
    unsigned int temp = n;
    int msb_pos = 0;
    
    while (temp > 1) {
        temp >>= 1;
        msb_pos++;
    }
    
    if (msb_pos < 2) {
        return n;
    }
    
    unsigned int mask = ((1U << (msb_pos - 1)) - 1) << 1;
    
    return n ^ mask;
}

int main(void) {
    unsigned int num = 10;
    unsigned int result = toggle_middle_bits(num);
    
    printf("%u\n", result);
    
    num = 11;
    result = toggle_middle_bits(num);
    printf("%u\n", result);
    
    return EXIT_SUCCESS;
}