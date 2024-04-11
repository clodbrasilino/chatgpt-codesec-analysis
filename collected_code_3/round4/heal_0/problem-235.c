#include <stdio.h>

unsigned int setEvenBits(unsigned int num) {
    unsigned int mask = 0xAAAAAAAA;
    return num | mask;
}

int main() {
    unsigned int num = 23;
    printf("Number after setting even bits: %u", setEvenBits(num));
    return 0;
}