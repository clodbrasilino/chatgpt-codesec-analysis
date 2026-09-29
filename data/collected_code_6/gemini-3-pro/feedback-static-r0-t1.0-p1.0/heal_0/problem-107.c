#include <stdio.h>
#include <stdlib.h>

unsigned int count_hex_numbers(unsigned int start, unsigned int end) {
    if (start > end) {
        return 0;
    }
    return end - start + 1;
}

int main(void) {
    unsigned int start = 0x10;
    unsigned int end = 0x2F;
    unsigned int count;

    count = count_hex_numbers(start, end);
    
    printf("%X\n", count);

    return 0;
}