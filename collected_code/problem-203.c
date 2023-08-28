#include <stdio.h>

int hammingDistance(int x, int y) {
    int xor = x ^ y;
    int distance = 0;
    
    while (xor != 0) {
        if (xor & 1) {
            distance++;
        }
        xor >>= 1;
    }
    
    return distance;
}

int main() {
    int a = 1;
    int b = 4;
    int distance = hammingDistance(a, b);
    
    printf("Hamming distance between %d and %d is %d\n", a, b, distance);
    
    return 0;
}