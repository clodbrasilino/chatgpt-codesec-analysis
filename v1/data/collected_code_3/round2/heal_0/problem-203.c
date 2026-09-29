#include <stdio.h>

int hammingDistance(int x, int y) {
    int xor = x ^ y;
    int distance = 0;
    while (xor) {
        distance += xor & 1;
        xor >>= 1;
    }
    return distance;
}

int main() {
    int x = 1;
    int y = 4;
    printf("Hamming Distance: %d", hammingDistance(x, y));
    return 0;
}