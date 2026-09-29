#include <stdio.h>

unsigned int rightmost_set_bit_position(unsigned int n) {
    if (n == 0) {
        return 0;
    }
    
    unsigned int position = 1;
    while ((n & 1) == 0) {
        n >>= 1;
        position++;
    }
    return position;
}

int main(void) {
    unsigned int num = 18;
    unsigned int pos = rightmost_set_bit_position(num);
    printf("%u\n", pos);
    return 0;
}