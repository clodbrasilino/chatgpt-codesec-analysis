#include <stdio.h>
#include <stdlib.h>

int hamming_distance(int x, int y) {
    unsigned int xor_val = (unsigned int)x ^ (unsigned int)y;
    int distance = 0;
    while (xor_val > 0) {
        distance += xor_val & 1;
        xor_val >>= 1;
    }
    return distance;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        return EXIT_FAILURE;
    }
    long val1 = strtol(argv[1], NULL, 10);
    long val2 = strtol(argv[2], NULL, 10);
    if (val1 > 2147483647 || val1 < -2147483648 || val2 > 2147483647 || val2 < -2147483648) {
        return EXIT_FAILURE;
    }
    int a = (int)val1;
    int b = (int)val2;
    int result = hamming_distance(a, b);
    printf("%d\n", result);
    return EXIT_SUCCESS;
}