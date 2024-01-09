#include<stdio.h>

unsigned int smallestPowerOfTwo(unsigned int n) {
    n--;

    n = n | (n >> 1);
    n = n | (n >> 2);
    n = n | (n >> 4);
    n = n | (n >> 8);
    n = n | (n >> 16);

    return n + 1;
}

int main() {
    unsigned int n = 10;
    unsigned int result = smallestPowerOfTwo(n);
    printf("Smallest power of 2 greater than or equal to %u is %u\n", n, result);

    return 0;
}