#include <stdio.h>

unsigned int toggleOddBits(unsigned int n) {
    unsigned int mask = 0xAAAAAAAA;
    return (n ^ mask);
}

int main() {
    unsigned int x = 23;
    printf("%u", toggleOddBits(x));
    return 0;
}