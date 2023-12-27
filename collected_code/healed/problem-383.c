#include<stdio.h>

unsigned int toggleOddBits(unsigned int num) {
    unsigned int mask = 0xAAAAAAAA;
    return num ^ mask;
}

int main() {
    unsigned int num = 0;
    printf("Enter a number: ");
    scanf("%u", &num);
    printf("Number with toggled odd bits: %u\n", toggleOddBits(num));
    return 0;
}