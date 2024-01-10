#include <stdio.h>
#include <limits.h>

unsigned int toggle_bits(unsigned int num) {

    int num_bits = sizeof(unsigned int) * CHAR_BIT;
    unsigned int mask = (1U << (num_bits - 1)) | 1;
    
    return num ^ mask;
}

int main() {
    unsigned int num = 10;
    unsigned int result = toggle_bits(num);
    printf("Result: %u\n", result);
    
    return 0;
}