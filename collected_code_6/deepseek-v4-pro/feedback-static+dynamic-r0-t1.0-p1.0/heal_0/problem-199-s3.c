#include <stdio.h>
#include <stdint.h>

unsigned int highestPowerOfTwo(unsigned int n) {
    if (n == 0) return 0;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    return n - (n >> 1);
}

int main(void) {
    unsigned int num;
    printf("Enter a number: ");
    if (scanf("%u", &num) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    printf("Highest power of 2 <= %u is %u\n", num, highestPowerOfTwo(num));
    return 0;
}