#include <stdio.h>
#include <stdlib.h>

unsigned int get_rightmost_set_bit_position(unsigned int n);

unsigned int get_rightmost_set_bit_position(unsigned int n) {
    unsigned int pos = 1;
    
    if (n == 0) {
        return 0;
    }
    
    while ((n & 1) == 0) {
        n >>= 1;
        pos++;
    }
    
    return pos;
}

int main(void) {
    unsigned int num = 18;
    unsigned int pos = get_rightmost_set_bit_position(num);
    
    if (pos > 0) {
        printf("%u\n", pos);
    } else {
        printf("0\n");
    }
    
    return EXIT_SUCCESS;
}