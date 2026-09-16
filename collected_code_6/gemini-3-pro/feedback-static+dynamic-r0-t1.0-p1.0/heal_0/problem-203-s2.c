#include <stdio.h>
#include <stdlib.h>

unsigned int hamming_distance(unsigned int x, unsigned int y);

unsigned int hamming_distance(unsigned int x, unsigned int y) {
    unsigned int xor_val = x ^ y;
    unsigned int distance = 0;

    while (xor_val > 0) {
        xor_val &= (xor_val - 1);
        distance++;
    }

    return distance;
}

int main(void) {
    unsigned int num1 = 0;
    unsigned int num2 = 0;

    if (scanf("%u %u", &num1, &num2) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    unsigned int distance = hamming_distance(num1, num2);
    
    printf("%u\n", distance);

    return EXIT_SUCCESS;
}