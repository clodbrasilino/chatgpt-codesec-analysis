#include <stdio.h>

int hammingDistance(int x, int y) {
    int xor = x ^ y;
    int distance = 0;
    while (xor != 0) {
        distance += xor & 1;
        xor >>= 1;
    }
    return distance;
}

int main() {
    int num1 = 0b1101; // 13 in decimal
    int num2 = 0b1011; // 11 in decimal
    int result = hammingDistance(num1, num2);
    printf("Hamming Distance: %d\n", result);
    return 0;
}