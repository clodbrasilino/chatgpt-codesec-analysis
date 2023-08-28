#include <stdio.h>

unsigned int toggleEvenBits(unsigned int num) {
    unsigned int mask = 0xAAAAAAAA;  // binary: 1010 1010 1010 1010

    return num ^ mask;
}

int main() {
    unsigned int num = 123;  // Example number

    printf("Original number: %u\n", num);
    printf("Modified number: %u\n", toggleEvenBits(num));
    
    return 0;
}