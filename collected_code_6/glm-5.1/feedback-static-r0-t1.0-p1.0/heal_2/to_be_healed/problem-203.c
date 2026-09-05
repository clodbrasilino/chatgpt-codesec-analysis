#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int hamming_distance(int x, int y) {
    unsigned int xor_val = (unsigned int)x ^ (unsigned int)y;
    int distance = 0;
    while (xor_val > 0) {
        distance += xor_val & 1;
        xor_val >>= 1;
    }
    return distance;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 3) {
        return EXIT_FAILURE;
    }
    long val1 = strtol(argv[1], NULL, 10);
    long val2 = strtol(argv[2], NULL, 10);
    if (val1 > INT_MAX || val1 < INT_MIN || val2 > INT_MAX || val2 < INT_MIN) {
        return EXIT_FAILURE;
    }
    int a = (int)val1;
    int b = (int)val2;
    int result = hamming_distance(a, b);
    printf("%d\n", result);
    return EXIT_SUCCESS;
}