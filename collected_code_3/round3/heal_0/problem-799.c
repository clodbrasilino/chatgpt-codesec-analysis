#include <stdio.h>

unsigned int leftRotate(unsigned int num, unsigned int rotation) {
    unsigned int bits = sizeof(num) * 8;
    rotation = rotation % bits;
    return (num << rotation) | (num >> (bits - rotation));
}

int main() {
    unsigned int num = 15;
    unsigned int rotation = 2;
    unsigned int result = leftRotate(num, rotation);
    printf("After left rotation of %u by %u bits: %u\n", num, rotation, result);
    return 0;
}