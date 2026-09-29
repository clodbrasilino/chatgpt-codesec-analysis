#include <stdio.h>

unsigned int leftRotate(unsigned int num, int rotations) {
    return (num << rotations) | (num >> (32 - rotations));
}

int main() {
    unsigned int number = 10; // Example number
    int rotations = 2; // Example rotations
    unsigned int result = leftRotate(number, rotations);
    printf("%u\n", result);
    return 0;
}