#include <stdio.h>

unsigned int toggleOddBits(unsigned int num) {
    // mask for all odd bits in an 32-bit integer
    unsigned int mask = 0xAAAAAAAA;

    // XOR num with mask of odd bits to toggle them
    return num ^ mask;
}

int main() {
    unsigned int num = 42;
    unsigned int result;

    result = toggleOddBits(num);

    printf("The result is: %u\n", result);

    return 0;
}