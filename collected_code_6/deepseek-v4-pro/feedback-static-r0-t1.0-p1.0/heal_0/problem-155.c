#include <stdio.h>

unsigned int toggle_even_bits(unsigned int num) {
    unsigned int mask = 0xAAAAAAAA;
    return num ^ mask;
}

int main(void) {
    unsigned int test_num = 0xFFFF;
    unsigned int result = toggle_even_bits(test_num);
    
    printf("Original: 0x%X\n", test_num);
    printf("Toggled:  0x%X\n", result);
    
    return 0;
}