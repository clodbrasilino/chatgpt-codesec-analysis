#include <stdio.h>

int hammingDistance(int x, int y) {
    int xorResult = x ^ y;
    int dist = 0;
    while (xorResult > 0) {
        dist += xorResult & 1;
        xorResult >>= 1;
    }
    return dist;
}

int main() {
    int a = 1;
    int b = 4;
    printf("Hamming Distance: %d\n", hammingDistance(a, b));
    return 0;
}