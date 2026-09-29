#include <stdio.h>

unsigned int setOddBits(unsigned int n) {
    unsigned int mask = 0xAAAAAAAA;
    return (n | mask);
}

int main() {
    unsigned int x = 10;
    printf("Result: %u\n", setOddBits(x));
    return 0;
}