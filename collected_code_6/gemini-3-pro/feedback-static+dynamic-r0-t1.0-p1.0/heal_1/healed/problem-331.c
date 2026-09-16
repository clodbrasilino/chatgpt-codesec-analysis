#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

unsigned int count_unset_bits(unsigned int n) {
    unsigned int count = 0;
    
    while (n > 0) {
        if ((n & 1) == 0) {
            count++;
        }
        n >>= 1;
    }
    
    return count;
}

unsigned int count_unset_bits_total(unsigned int n) {
    if (n == 0) {
        return sizeof(unsigned int) * CHAR_BIT;
    }
    
    unsigned int count = 0;
    unsigned int total_bits = sizeof(unsigned int) * CHAR_BIT;
    
    for (unsigned int i = 0; i < total_bits; i++) {
        if ((n & (1U << i)) == 0) {
            count++;
        }
    }
    
    return count;
}

int main(void) {
    unsigned int num = 25;
    unsigned int unset_bits = count_unset_bits_total(num);
    
    printf("%u\n", unset_bits);
    
    return EXIT_SUCCESS;
}