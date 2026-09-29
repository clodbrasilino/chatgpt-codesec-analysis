#include <stdio.h>
#include <stdlib.h>

unsigned int hamming_distance(int a, int b) {
    unsigned int distance = 0;
    int xor_result = a ^ b;

    while (xor_result) {
        distance += xor_result & 1;
        xor_result >>= 1;
    }

    return distance;
}

int main() {
    int a, b;

    printf("Enter first integer: ");
    if (scanf("%d", &a) != 1) {
        printf("Failed to read the first integer\n");
        exit(1);
    }

    printf("Enter second integer: ");
    if (scanf("%d", &b) != 1) {
        printf("Failed to read the second integer\n");
        exit(1);
    }

    printf("Hamming distance: %u\n", hamming_distance(a, b));

    return 0;
}